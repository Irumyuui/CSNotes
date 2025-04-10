# Compare and Swap

## 乐观锁

乐观锁即为假定并发条件下不会引发冲突的一类锁。如果没有并发冲突，那么也就不需要加锁，也就不会花费到加锁的开销了。在乐观锁的状态下，加锁操作换成了去完成某次操作，在操作完成并提交时再来检查数据完整性。如果本次操作因为并发冲突导致失败，则需要对原本的操作进行**重试**，直到成功为止。

## CAS (Comapre and Set / Compare and Swap)

CAS 操作即为上述介绍中的重试操作，由 CPU 保证该过程一定是原子的。如果该对象的值与期待的值相等，那么赋予该对象新值，否则通过期待的值的地址传回旧对象现在的值。

> 为什么需要设计为传回对象现在的值？因为如果分开的话，`load` 与上次的操作不是在一个原子操作内完成的，这样会导致数据一致性的问题。

```c++
// 一个演示，该过程由 CPU 保证原子性，示例代码不保证原子性
bool compare_and_swap(
    int *obj,
    int *excpected_value,
    int new_value
) {
    if (*obj == *excpected_value) {
        *obj = new_value;
        return true;
    }

    *excpected_value = *obj;
    return false;
}
```

### comapre_exchange_strong and compare_exchange_weak

那么既然是 CAS 操作，`compare_exchange_strong` 和 `compare_exchange_weak` 这两个函数的区别是什么呢？

答案是：在某些体系结构实现中，`comapre_exchange_weak` 实际上会会导致**虚假失败**，也就是虽然 `CAS` 操作返回成功了，但是实际上操作失败了。

因此，对于这种情况，`weak` 版本的操作通常放在一个循环内，且循环判断的第二个操作即为判断结果。

```c++
// std::atomic<bool> flag; // 一个不知道哪里的 flag
bool expected = false;

// 前面失败了，但实际上其实是成功了
while (!flag.compare_exchange_weak(expected, true) && !expected) {
}
```

但实际上即使是 `strong` 版本也经常是在循环中进行判断。对于 `strong` 版本来说，他不会导致虚假失败，但是依然会在并发写入时失败（也就是 `CAS` 失败），这也就是乐观锁失败。

```c++
while (!flag.compare_exchange_strong(expected, true)) {
}
```

### 为什么需要 weak

实际上，对于虚假失败来说其实并不会经常发生，一般来说这样对性能的影响并不大，通常 `expected` 的变量并非原子访存，也不需要对其考虑并发问题。并且，在某些平台上其性能表现要好于 `strong` 版本，因为 `strong` 版本必须检查虚假失败，甚至有些平台上 `strong` 版本的实现就是 `weak` 版本加上循环的实现。

如果一点点小小的失败对并不是什么大问题，那么在性能问题前其实也无关紧要了。

### 如何选择 weak 和 strong

如果 `CAS` 操作需要在循环中进行判断，那么选择 `weak` 版本的性能就比较合适。如果使用 `weak` 需要循环，而 `strong` 不需要循环时，那么自然选择 `strong` 版本。

总结来说一句话：**如果只是因为虚假失败导致需要引入循环，那么直接使用 `strong` 版本，如果一定有个循环，那么选择 `weak` 版本。**问题很简单。

## ABA Problem

多线程问题中，如果一个线程对一个内存位置读取两次值，且这两次的值是一样的，那么这个变量一定没被动过吗？

答案是：不是。另外一个线程可以在这期间偷偷动一下变量，然后又还回去了，此时实际上内存值已经发生了改变，只是它回去了而已。这种情况被称为 **ABA 问题**。

一般来说，如果值是一样的，那么其实也无所谓。但是这样的操作，总是会导致一些潜在的操作逻辑发生。

> 虽然存在 ABA 问题，但是如果涉及到的预期代码行为不是很重要，或者数据允许出点小错误，那么 ABA 问题甚至是可以被允许的。

一个常见的例子是：实现无锁数据结构。比如实现一个无锁链表，从其中一个位置删除，并立刻申请内存添加回去，此时由于内存适配器对此处内存可能进行复用，将导致这个元素的内存地址未发生变化，但确实并不是同一个元素。如果 `CAS` 操作的对象时地址，那么此时可能出现一个情况：某个线程发现自己持有的地址变成了悬垂地址。

要解决 ABA 问题，则可以简单的加入一个标记，例如修改的次数，作为**版本号**。最简单的方式即为在指针地址中未被利用的地址作为标记，这样 `CAS` 操作则不会出现 ABA 问题。如果惧怕出现回环问题（即无符号整数溢出），那么甚至可以直接使用 128 位地址作为 CAS 操作。
