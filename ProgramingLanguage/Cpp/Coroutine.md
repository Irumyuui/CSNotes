# c++20 协程

## 关键字

- `co_await`：暂停和恢复的点，等待另外一个协程
- `co_yield`：暂停该协程，然后给绑定的 `promise_type` 对象填入一个值
- `co_return`：给绑定的 `promise_type` 对象填入一个值，然后结束该协程

