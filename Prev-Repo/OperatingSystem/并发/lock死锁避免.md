# std::lock 死锁避免

> 避免死锁的一个简单方式是按统一顺序进行上锁。

`std::lock` 用于对多把锁进行按顺序上锁的一个辅助函数，里面包含了一个死锁避免算法。

死锁避免具体是怎么做的？首先是按顺序对一把锁进行上锁，并对接下来的一把锁尝试进行上锁，如果上锁成功，那么继续这个过程直到所有锁上锁。如果中间这个过程出现上锁失败，那么该线程将经过一次切换以后，通过相反的顺序再尝试上述的步骤，直到所有锁都成功上锁为止。

## c++17 之前的实践

`c++17` 之前需要先对所有锁进行上锁，然后使用 `std::lock_guard` 管理上锁的行为，`std::adopt_lock` 只是标记一下锁已经上了不用初始化的时候再次上锁。

> 其实我觉得这里使用模板变量不更好吗

```c++
std::mutex mtx1, mtx2;

std::lock(mtx1, mtx2);
std::lock_guard<std::mutex> lock1(mtx1, std::adopt_lock);
std::lock_guard<std::mutex> lock2(mtx2, std::adopt_lock);
```

## c++17 之后的实践

等价于上述的方式。

```c++
std::mutex mtx1, mtx2;

std::scoped_lock lock{mtx1, mtx2};
```
