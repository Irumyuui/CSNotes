use std::ops::{Deref, DerefMut};
use std::sync::Arc;
use std::{cell::UnsafeCell, sync::atomic::AtomicBool};

use std::sync::atomic::Ordering as AtomicOrdering;

pub struct SpinLock<T> {
    lock: AtomicBool,
    data: UnsafeCell<T>,
}

unsafe impl<T> Sync for SpinLock<T> where T: Send {}

impl<T> SpinLock<T> {
    pub fn new(data: T) -> Self {
        Self {
            lock: AtomicBool::new(false),
            data: UnsafeCell::new(data),
        }
    }

    pub fn lock(&self) -> SpinLockGuard<T> {
        // 成功，位于这条 加载-修改-存储 指令之后的访存指令因为被禁止重排到前面，所以一定能看到这条语句的结果，算是通知其他的位置，让他们也能看到锁的状态
        // 失败，随便
        while self
            .lock
            .compare_exchange_weak(
                false,
                true,
                AtomicOrdering::Acquire,
                AtomicOrdering::Relaxed,
            )
            .is_err()
        {}

        SpinLockGuard { lock: self }
    }
}

pub struct SpinLockGuard<'a, T> {
    lock: &'a SpinLock<T>,
}

impl<T> Drop for SpinLockGuard<'_, T> {
    fn drop(&mut self) {
        // 确保在释放锁之前的所有内存操作（读或写）不会被重排到释放锁之后
        // 当此条指令的结果对其他线程可见后，之前的所有指令都可见
        // 也算是通知其他的位置，让他们也能看到释放锁的指令
        self.lock.lock.store(false, AtomicOrdering::Release);
    }
}

impl<T> Deref for SpinLockGuard<'_, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        unsafe { &*self.lock.data.get() }
    }
}

impl<T> DerefMut for SpinLockGuard<'_, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { &mut *self.lock.data.get() }
    }
}

fn main() {
    let data = Arc::new(SpinLock::new(5));

    let tmp = data.clone();
    let t1 = std::thread::spawn(move || {
        let _data = tmp.lock();
        println!("into t1");
        std::thread::sleep(std::time::Duration::from_millis(1000));
    });

    let tmp = data.clone();
    let t2 = std::thread::spawn(move || {
        let _data = tmp.lock();
        println!("into t2");
        std::thread::sleep(std::time::Duration::from_millis(1000));
    });

    t1.join().unwrap();
    t2.join().unwrap();
}
