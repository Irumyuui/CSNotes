# static 线程安全的原因

> 讲真谁问了……就想揍人一顿。

![传送门](https://github.com/llvm/llvm-project/blob/main/libcxxabi/src/cxa_guard.cpp)

众所周知，`c++11` 开始实现线程安全的单例模式是这儿做的。

```c++
class Foo {
public:
    static Foo& getInstance() {
        static Foo foo{};
        return foo;
    }
}
```

但是是如何保证的呢……其实还是加了锁，不过是由运行时来做的。一般的实现就是类似于 `libc++` 的实现。
