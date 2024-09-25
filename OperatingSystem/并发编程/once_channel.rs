use core::panic;
use std::marker::PhantomData;
use std::sync::{Arc, Once};
use std::{cell::UnsafeCell, mem::MaybeUninit, sync::atomic::AtomicBool};

use std::sync::atomic::Ordering as AtomicOrdering;

pub struct OnceChannel<T> {
    message: UnsafeCell<MaybeUninit<T>>,
    ready: AtomicBool,
}

unsafe impl<T> Sync for OnceChannel<T> where T: Send {}

impl<T> OnceChannel<T> {
    pub const fn new() -> Self {
        Self {
            message: UnsafeCell::new(MaybeUninit::uninit()),
            ready: AtomicBool::new(false),
        }
    }

    pub fn split(&mut self) -> (OnceSender<'_, T>, OnceReceiver<'_, T>) {
        (
            OnceSender {
                channel: self,
                recv_thread: std::thread::current(),
            },
            OnceReceiver {
                channel: self,
                _no_send_marker: PhantomData,
            },
        )
    }
}

impl<T> Drop for OnceChannel<T> {
    fn drop(&mut self) {
        if !*self.ready.get_mut() {
            unsafe {
                self.message.get_mut().assume_init_drop();
            }
        }
    }
}

pub struct OnceSender<'a, T> {
    channel: &'a OnceChannel<T>,
    recv_thread: std::thread::Thread,
}
pub struct OnceReceiver<'a, T> {
    channel: &'a OnceChannel<T>,
    _no_send_marker: PhantomData<*const ()>,
}

impl<T> OnceSender<'_, T> {
    pub fn send(self, message: T) {
        unsafe {
            (*self.channel.message.get()).write(message);
        }

        self.channel.ready.store(true, AtomicOrdering::Release);
        self.recv_thread.unpark();
    }
}
impl<T> OnceReceiver<'_, T> {
    pub fn recv(&self) -> T {
        while !self.channel.ready.swap(false, AtomicOrdering::Acquire) {
            std::thread::park();
        }

        unsafe { (*self.channel.message.get()).assume_init_read() }
    }

    pub fn is_ready(&self) -> bool {
        self.channel.ready.load(AtomicOrdering::Acquire)
    }
}

fn main() {}
