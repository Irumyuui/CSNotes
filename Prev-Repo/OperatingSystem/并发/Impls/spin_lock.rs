use std::{
    cell::UnsafeCell,
    ops::{Deref, DerefMut},
    sync::atomic::{AtomicBool, Ordering as AtomicOrdering},
};

pub struct SpinLock<T> {
    lock_flag: AtomicBool,
    data: UnsafeCell<T>,
}

unsafe impl<T> Sync for SpinLock<T> {}

struct SpinLockGuard<'lock, T> {
    inner: &'lock SpinLock<T>,
}

impl<T> SpinLock<T> {
    pub const fn new(data: T) -> Self {
        Self {
            lock_flag: AtomicBool::new(false),
            data: UnsafeCell::new(data),
        }
    }

    // 成功，位于这条 加载-修改-存储 指令之后的访存指令因为被禁止重排到前面，所以一定能看到这条语句的结果，算是通知其他的位置，让他们也能看到锁的状态
    // 失败，随便
    pub fn lock<'lock>(&'lock self) -> SpinLockGuard<'lock, T> {
        while self
            .lock_flag
            .compare_exchange_weak(
                false,
                true,
                AtomicOrdering::Acquire,
                AtomicOrdering::Relaxed,
            )
            .is_err()
        {}

        SpinLockGuard { inner: self }
    }
}

impl<'lock, T> Drop for SpinLockGuard<'lock, T> {
    // 确保在释放锁之前的所有内存操作（读或写）不会被重排到释放锁之后
    // 当此条指令的结果对其他线程可见后，之前的所有指令都可见
    // 也算是通知其他的位置，让他们也能看到释放锁的指令
    fn drop(&mut self) {
        self.inner.lock_flag.store(false, AtomicOrdering::Release);
    }
}

impl<'lock, T> Deref for SpinLockGuard<'lock, T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        unsafe { &*self.inner.data.get() }
    }
}

impl<'lock, T> DerefMut for SpinLockGuard<'lock, T> {
    fn deref_mut(&mut self) -> &mut Self::Target {
        unsafe { &mut *self.inner.data.get() }
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
