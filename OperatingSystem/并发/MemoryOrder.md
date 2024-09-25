# Memory Order

总所周知，多线程编程中总有两个大问题：数据竞争、内存执行顺序。

## 数据竞争（Data Racing）

什么是数据竞争？想象现在你和你的兄弟，放假回家，但是你家里只有一台电脑，你们两个抢了一个鼠标和一个键盘，那么此时电脑就被竞争了。

回到多线程编程，数据竞争就是以下的情况：

```c++
#include <cassert>
#include <print>
#include <thread>
#include <ranges>
#include <vector>

int count = 0;

void add_count() {
    for (int i = 0; i < 1000000; i ++) {
        ++ count;
    }
}

int main() {
    auto vec = std::ranges::views::iota(0, 2)
        | std::views::transform([](int _) { return std::jthread(add_count); })
        | std::ranges::to<std::vector>();

    for (auto& t : vec) {
        t.join();
    }

    std::println("count = {}", count);
}
```

实际上两个线程互相争夺 `count` 了。但是为什么输出结果不是期望值呢？思考以下代码的执行：

```c++
++ count;
```

如果改写为汇编，那么实际的代码为（伪代码）：

```text
// temp 是一个寄存器
temp <- count;      // 读取
temp = temp + 1;    // 计算 + 1 ，这个是保障原子性的
count <- temp;      // 保存
```

多线程的问题出现在哪里？因为这一条语句没办法保证，两个线程执行过程中，是不是 a 线程计算完之后、保存之前，b 线程读了一个旧值。这就带来了这个问题：数据竞争。

## 解决数据竞争

如何解决数据竞争呢？使用 `atomic` 。

```rust
use std::sync::{atomic::AtomicI32, Arc};

use std::sync::atomic::Ordering as AtomicOrdering;

fn main() {
    let x = Arc::new(AtomicI32::new(0));

    (0..2)
        .into_iter()
        .map(|_| {
            let x = Arc::clone(&x);
            std::thread::spawn(move || {
                for _ in 0..1000000 {
                    x.fetch_add(1, AtomicOrdering::SeqCst);
                }
            })
        })
        .for_each(|t| {
            let _ = t.join();
        });

    println!("Final value: {}", x.load(AtomicOrdering::SeqCst));
}
```

## 什么是原子操作

简单来说，就是对一个内存上变量的读取-变更-存储（land and store）作为一个整体，一次完成。

回过头看看我们刚刚的伪代码：

```asm
load a t1
add a
store a t1
```

对于这三条汇编指令，他们各自已经是原子的了，但是他们组合在一起的结果呢？不是。换句话说，原子操作就是对这样的语句组合，给上了一个更加轻量级的锁，让他们能够密不可分的执行完毕，而不是中间（这里请将多线程执行直接并和到单线程中）突然被 ntr ，插入了外来的语句。

回到我们现在的一个问题：我们做的是 `x++` ，也就是一个变量的自增。那如果在这个变量周围，还有一个变量呢执行：`y++` 呢？

注意我们现在不是讨论多线程的问题了，而是单线程下，`x++` 和 `y++` ，这两个语句的执行顺序。

假设，我们假设 `x` 和 `y` 都是原子变量，那么存在一个问题：

```c++
x++;
y++;
```

他真的是先 `x++` ，再 `y++` 吗？显然这个问题的答案是：不一定。

对于编译器而言，代码都是单线程下的，编译器也是按照单线程下的代码进行优化，那么这里就涉及到一个问题：编译器会对你的代码进行重排。哦天啊！那我直接不让编译器重排可以吗？也不行。

即使是编译器重排，那么也只是二进制中顺序不一样，对于多个核心，他们执行的都是同一份二进制，所以其实也没太大关系，关键在于，**现代 CPU 会重排指令**。为什么？因为当代 CPU 除了一个多核以外，每个核心里面可能还有多套重复的部件，内部也可以同时进行任务，从而做到多发射以及乱序发射指令的效果。

回到刚刚说的，原子性的问题，对于单条 `x++` ，我们说了他就像上了一个单独的锁，对于其他的 CPU 来说，也就是上了一个锁，想要对这个变量执行操作，要么是在这个 CPU 执行这条指令之前，要么是之后。也可以说，**这条原子指令直接告诉了多个线程之间，其他指令执行的先后顺序**，即：**这次原子操作就是一个锚点**，由于原子操作是不可分割的，因此来自不同线程的对同一对象的第二次原子操作只能在第一个原子操作之前或之后获取该对象的状态。。

那么其他的原子指令怎么办？它们的顺序和本次原子操作有什么关系？那就来个 memory_order 了。

## 内存序

> 基于其 memory_order 参数，原子操作为**同一线程**中其他原子操作的效果的可见性建立排序要求。因此，它会禁止违反排序要求的编译器优化。

实际上，内存序并不是针对于多线程的，而是针对于**单线程**中，出现的编译器重排和 CPU 乱序执行指令的问题，按照对于原子变量的要求，甚至禁止掉这种的指令重排。

简单来说：memory_order 解决的是在当前线程的当前原子操作，对于其他操作的可见性顺序问题。

简单来说，有以下语句：

```c++
a = b + c;
d = e + a;
```

多线程下要保证正确，那么我一定要求执行 `d = e + a` 时候，`a = b + c` 我能看见他的结果，内存序就这样。

<!-- https://github.com/apache/brpc/blob/master/docs/cn/atomic_instructions.md#memory-fence -->

| Memory Order | 作用 |
| :---: |:---:|
| relaxd | 啥都没约束到 |
| comsume | 后面**依赖于这个原子变量**的访存指令请勿重排到这条指令之前 |
| acquire | 后面的访存指令请勿重排到这条指令之前 |
| release | 前面的访存指令请勿重排到这条指令。当此条指令的结果对其他线程可见后，之前的所有指令都可见 |
| acq_rel | acquire + release |
| seq_cst | acquire + release ，还有所有使用了 seq_cst 的指令一定有严格的偏序关系 |

简单来说，以以下这个例子，ready 为 true 的时候，我要怎么让 t2 知道 p 已经好了呢？

```c++
// Thread 1
// bool ready was initialized to false
p.init();
ready = true;

// Thread2
if (ready) {
    p.bar();
}
```

relase 和 acquire 即可。

> 似乎除了最严格的 seq ，其他的就 relaxed 和这两个用最多？

```c++
// Thread 1
// std::atomic<bool> ready was initialized to false
p.init();
// 前面的访存指令，乖乖排前面，这样的一个好处是，只要读到这条语句的结果，那么也意味着这个语句之前的访存指令结束了
ready.store(true, std::memory_order_release);

// Thread2
// 在这条语句之后的访存指令，乖乖排后面，别干扰操作
if (ready.load(std::memory_order_acquire)) {
    p.bar();
}
```

## std::atomic 如何做到原子性

实际上，`std::atomic` ，还是 rust 的 `std::sync::atomic` ，都是使用**底层硬件支持的原子操作指令**，这些原子指令在执行时被保证不会被其他线程中断。

- 缓存一致性协议：这个会告诉不同的 core ，告诉对应变量的状态，然后决定是否要从存储中重新读取值
- 总线锁定：一些原子操作在执行的时候，会锁定 CPU 的总线，这样其他 CPU 就不能同时修改同一处内存位置了

引用知乎上的一篇回答（因为我不懂缓存一致性协议和总线的事情）：

> X86架构CPU的话，会用缓存一致性协议和CacheLine Lock来实现这个原子性。
> 前者会告诉不同的core对应的变量的状态，是否要从存储中重新读取避免读到旧值（这里的存储包括L3Cache），目前的缓存一致性协议基于MESIF，对应的状态机有兴趣去看看。
> 当然，单凭缓存一致性协议不能保证读取-修改-写这个操作的原子性，还需要用到CacheLineLock，当一个core试图执行原子操作时，这个core发出"Read Invalidate"消息广播给其他core，其他CPU core将原子变量所在的缓存无效（见上面提到的MESIF协议），并从Cache返回数据。该core将Cache line置成Exclusive状态。然后将该CacheLine标记上锁，然后读取原子变量，修改，最后写入cache line。写完将cache line置位unlocked。
> 原子操作开销严格来说不小，做低时延开发时能不用就别用。

