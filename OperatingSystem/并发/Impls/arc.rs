use std::cell::UnsafeCell;
use std::mem::ManuallyDrop;
use std::ops::Deref;
use std::usize;
use std::{ptr::NonNull, sync::atomic::AtomicUsize};

use std::sync::atomic::{fence, Ordering as AtomicOrdering};

struct RefCounter<T> {
    /// data 的生命周期，当计数达到 0 时，drop data
    data_ref_count: AtomicUsize,
    /// RefCounter 的生命周期，当计数达到 0 时，drop RefCounter
    alloc_ref_count: AtomicUsize,
    /// 指向 data ，手动控制生命周期
    data: UnsafeCell<ManuallyDrop<T>>,
}

pub struct Arc<T> {
    ptr: NonNull<RefCounter<T>>,
}

pub struct Weak<T> {
    ptr: NonNull<RefCounter<T>>,
}

// T 在多线程共享情况下，会出现所有权转移到另一个线程（Send）和所有权共享（Sync）的问题
unsafe impl<T> Send for Arc<T> where T: Send + Sync {}
unsafe impl<T> Sync for Arc<T> where T: Send + Sync {}

unsafe impl<T> Send for Weak<T> where T: Send + Sync {}
unsafe impl<T> Sync for Weak<T> where T: Send + Sync {}

impl<T> Arc<T> {
    pub fn new(data: T) -> Arc<T> {
        Arc {
            ptr: NonNull::from(Box::leak(Box::new(RefCounter {
                data_ref_count: AtomicUsize::new(1),
                alloc_ref_count: AtomicUsize::new(1),
                data: UnsafeCell::new(ManuallyDrop::new(data)),
            }))),
        }
    }

    fn data(&self) -> &RefCounter<T> {
        unsafe { self.ptr.as_ref() }
    }

    pub fn downgrade(arc: &Self) -> Weak<T> {
        let mut n = arc.data().alloc_ref_count.load(AtomicOrdering::Relaxed);
        loop {
            // 检查是不是当前所有权被独占了，一般这种情况可以来一个自旋锁解决
            if n == usize::MAX {
                std::hint::spin_loop();
                n = arc.data().alloc_ref_count.load(AtomicOrdering::Relaxed);
                continue;
            }

            // 尝试引用计数块自增 1
            if let Err(e) = arc.data().alloc_ref_count.compare_exchange(
                n,
                n + 1,
                AtomicOrdering::Acquire,
                AtomicOrdering::Relaxed,
            ) {
                n = e;
                continue;
            }

            return Weak { ptr: arc.ptr };
        }
    }

    pub fn get_mut(arc: &mut Arc<T>) -> Option<&mut T> {
        // 独占所有权时必须要上锁
        if arc
            .data()
            .alloc_ref_count
            .compare_exchange(
                1,
                usize::MAX,
                AtomicOrdering::Acquire,    // 提醒后面 downgrade 这边已经写入了
                AtomicOrdering::Relaxed,
            )
            .is_err()
        {
            return None;
        }

        let is_unique = arc.data().data_ref_count.load(AtomicOrdering::Relaxed) == 1;
        arc.data().alloc_ref_count.store(1, AtomicOrdering::Release);  // 约束后面 downgrade ，我这上锁完毕了

        if !is_unique {
            None
        } else {
            fence(AtomicOrdering::Acquire);
            unsafe { Some(&mut *arc.data().data.get()) }
        }
    }
}

impl<T> Deref for Arc<T> {
    type Target = T;

    fn deref(&self) -> &Self::Target {
        let data_ptr = self.data().data.get();
        unsafe { &*data_ptr }
    }
}

impl<T> Clone for Arc<T> {
    fn clone(&self) -> Arc<T> {
        // 资源引用 +1
        self.data()
            .data_ref_count
            .fetch_add(1, AtomicOrdering::Relaxed);
        Arc { ptr: self.ptr }
    }
}

impl<T> Drop for Arc<T> {
    fn drop(&mut self) {
        // 如果强引用减到 0 时，意味着该指针生命周期完全结束，直接释放掉两个对象资源
        if self
            .data()
            .data_ref_count
            .fetch_sub(1, AtomicOrdering::Release)
            == 1
        {
            fence(AtomicOrdering::Acquire);
            unsafe {
                ManuallyDrop::drop(&mut *self.data().data.get());
            }
            drop(Weak { ptr: self.ptr });
        }
    }
}

impl<T> Weak<T> {
    fn data(&self) -> &RefCounter<T> {
        unsafe { self.ptr.as_ref() }
    }

    pub fn upgrade(&self) -> Option<Arc<T>> {
        // 需要持有资源的引用计数 +1
        let mut n = self.data().data_ref_count.load(AtomicOrdering::Relaxed);
        loop {
            if n == 0 {
                return None;
            }

            if let Err(e) = self.data().data_ref_count.compare_exchange_weak(
                n,
                n + 1,
                AtomicOrdering::Relaxed,
                AtomicOrdering::Relaxed,
            ) {
                n = e;
                continue;
            }

            return Some(Arc { ptr: self.ptr });
        }
    }
}

impl<T> Clone for Weak<T> {
    fn clone(&self) -> Weak<T> {
        self.data()
            .alloc_ref_count
            .fetch_add(1, AtomicOrdering::Relaxed);

        Weak { ptr: self.ptr }
    }
}

impl<T> Drop for Weak<T> {
    fn drop(&mut self) {
        if self
            .data()
            .alloc_ref_count
            .fetch_sub(1, AtomicOrdering::Release)
            == 1
        {
            fence(AtomicOrdering::Acquire);
            unsafe {
                drop(Box::from_raw(self.ptr.as_ptr()));
            }
        }
    }
}

#[test]
fn test() {
    static NUM_DROPS: AtomicUsize = AtomicUsize::new(0);

    struct DetectDrop;

    impl Drop for DetectDrop {
        fn drop(&mut self) {
            NUM_DROPS.fetch_add(1, AtomicOrdering::Relaxed);
        }
    }

    // Create an Arc with two weak pointers.
    let x = Arc::new(("hello", DetectDrop));
    let y = Arc::downgrade(&x);
    let z = Arc::downgrade(&x);

    let t = std::thread::spawn(move || {
        // Weak pointer should be upgradable at this point.
        let y = y.upgrade().unwrap();
        assert_eq!(y.0, "hello");
    });
    assert_eq!(x.0, "hello");
    t.join().unwrap();

    // The data shouldn't be dropped yet,
    // and the weak pointer should be upgradable.
    assert_eq!(NUM_DROPS.load(AtomicOrdering::Relaxed), 0);
    assert!(z.upgrade().is_some());

    drop(x);

    // Now, the data should be dropped, and the
    // weak pointer should no longer be upgradable.
    assert_eq!(NUM_DROPS.load(AtomicOrdering::Relaxed), 1);
    assert!(z.upgrade().is_none());
}

fn main() {}
