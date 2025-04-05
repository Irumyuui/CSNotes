# CSP 模式

CSP 模式，即 `Communicating Sequential Process` ，中文翻译过来就是通信顺序进程。

简单来说，它通过将多个线程之间的通信抽象为一个管道，来实现线程之间的通信（包括进程的）。

- 对于消息的生产者，只需要将消息放到管道里面就好，至于发送给了谁，不管了。
- 对于消息的消费者，只需要从管道里面取出消息就好，至于是谁发送的消息，不管的。

```c++
template <typename T>
class Channel
{
public:
    explicit Channel(std::size_t capacity = 0) : capacity_(capacity) {}

    bool Send(this Channel &self, T value)
    {
        std::unique_lock lock{ self.mutex_ };
        self.cv_producer_.wait(lock, [&self]
            {
                return (self.capacity_ == 0 && self.queue_.empty()) || self.queue_.size() < self.capacity_ || self.is_closed_;
            });

        if (self.is_closed_)
        {
            return false;
        }

        self.queue_.emplace(std::move(value));
        self.cv_consumer_.notify_one();

        return true;
    }

    bool Receive(this Channel &self, T& value)
    {
        std::unique_lock lock{ self.mutex_ };
        self.cv_consumer_.wait(lock, [&self]
            {
                return !self.queue_.empty() || self.is_closed_;
            });

        if (self.is_closed_ && self.queue_.empty())
        {
            return false;
        }

        value = std::move(self.queue_.front());
        self.queue_.pop();
        self.cv_producer_.notify_one();
        return true;
    }

    void Close(this Channel &self)
    {
        std::scoped_lock lock{ self.mutex_ };
        self.is_closed_ = true;
        self.cv_producer_.notify_all();
        self.cv_consumer_.notify_all();
    }

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cv_producer_;
    std::condition_variable cv_consumer_;
    std::size_t capacity_;
    bool is_closed_{ false };
};
```
