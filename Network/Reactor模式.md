# Reactor 模式

> Reactor：能收了你跟俺说一声。

`Reactor` 模型主要是用来作为对事件进行响应的方式。

对于这个模式，其实有另外一个更为贴切的叫法，即：`Dispatcher` 模式。直译就是分发模式。简单来说，其实就是**使用 IO 多路复用监听事件，在收到事件之后，根据事件把事件分配给某个进程/线程**。

比如在之前 `IOCP` 还有个专门处理回调函数的线程，就是为了预防其他线程忙于处理事件导致回调函数没办法处理。

- Reactor 负责监听和分发事件，事件比如连接、IO
- 一些东西，比如线程池，或者数据库连接池，负责处理事件

## 单 Reactor 单线程

在单独的一个线程/进程里面，监听和分发事件，然后给某个东西去处理事件。

> 下面代码其实只是一个线程池中处理事件的一个任务队列，不过很符合模式，在这里 `Post` 方法接收需要处理的事件，然后 `Run` 就来处理事件。
> 这里只是一个示范，没有线程的睡眠。

```csharp
public class EventPool
{
    private ConcurrentQueue<Action> _actions = [];

    public void Post(Action action) {
        _actions.Enqueue(action);
    }  

    public void Run() {
        while (true) {
            if (_actions.TryDequeue(out var action)) {
                action.Invoke();
            }
        }
    }
}
```

因为只有一个线程，那么就不需要考虑线程同步的问题。但是有一些缺点：

- 因为只有一个线程，现代 CPU 的多核性能没办法被利用了
- 因为只有一个线程，所以下面在处理 `action` 的时候，是没办法再分发事件的

不过这玩意写得方式很简单，毕竟最简单的实现其实就是单线程下的方式，很自然的处理方式。

## 单 Reactor 多线程

毕竟单线程还是有点浪费 CPU 了，并且也很难处理并发请求。

不过现在就是一个单 Reactor 多线程的模式了（虽然有点不像）。

```csharp
public sealed class TinyThreadPool
{
    private static readonly BlockingCollection<(Action, ExecutionContext?)> _workItems = [];

    private static readonly Thread[] _threads;

    public static void QueueUserWorkItem(Action workItem) => _workItems.Add((workItem, ExecutionContext.Capture()));

    static TinyThreadPool() {
        _threads = new Thread[Environment.ProcessorCount];
        for (int i = 0; i < _threads.Length; i ++) {
            _threads[i] = new Thread(() => {
                while (true) {
                    var (workItem, context) = _workItems.Take();
                    if (context is null) {
                        workItem();
                    } else {
                        ExecutionContext.Run(context, state => (state as Action)!.Invoke(), workItem);
                    }
                }
            }) {
                IsBackground = true
            };
            _threads[i].Start();
        }
    }
}
```

外部的 Reactor 线程监听一些东西，比如事件，监听到一个可以被执行的事件之后就可以通过 `QueueUserWorkItem` 将事件给线程池，线程池这边将事件分发给某个线程，让这个线程去执行事件。

## 多 Reactor 单线程

一个线程让一个 Reactor 监听不就好了，多个监听干嘛，不如都丢给一个监听，反正处理事件都是单线程。

## 多 Reactor 多线程

多 Reactor 多线程，就是为每个工作线程分配给单独一个 Reactor ，然后主线程有一个主 Reactor 负责接收事件，接收后不管直接丢给某个线程的 Reactor ，看是要监听还是处理，主线程不管子线程的东西。
