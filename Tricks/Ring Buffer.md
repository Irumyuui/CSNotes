Ring buffer ，其实就是一个环形数组，也许在以下地方见到过：

- 网卡的缓冲区
- rust 的 `VecDeque`
- tokio 的底层任务队列实现

为什么需要 ring buffer ？

- **好实现**，特别无锁结构
- 不关心内存
- cache 友好

不好做的地方？

- 长度固定，不是很好处理

c++ 的 `Deque` 实际上采取了一种非常不好的设计，最后实际上表现不是很优秀，如果可以的话，可以参照 rust 的 `VecDeque` 设计，后者就是基于 Ring Buffer 实现的。