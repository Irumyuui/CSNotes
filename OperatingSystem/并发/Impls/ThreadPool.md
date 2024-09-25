# 线程池

线程池维护一个任务队列和多个线程实例，当有任务需要执行时，线程池会将任务放入队列，并通知一个空闲线程来执行任务。通过预先开启多个线程，来优化掉线程创建和销毁的消耗。

```c++
class ThreadPool
{
public:
    static ThreadPool& Instance()
    {
        static ThreadPool pool;
        return pool;
    }

    ~ThreadPool() 
    {
        Stop();
    }

    template <typename F, typename ...Args>
    auto Submit(this ThreadPool &self, F &&f, Args &&...args) -> std::future<decltype(f(std::forward<Args>(args)...))>
    {
        using RetType = decltype(f(std::forward<Args>(args)...));

        if (self.stop_.load())
            return {};

        auto task = std::make_shared<std::packaged_task<RetType()>>([&f, args = std::forward_as_tuple(args...)]
        {
                return std::apply(f, args);
        });

        auto result = task->get_future();
        {
            std::scoped_lock lock{ self.cv_mutex_ };
            self.tasks_.emplace([task]
                {
                    (*task)();
                });
        }
        self.cv_lock_.notify_one();

        return result;
    }

private:
    ThreadPool(std::size_t num_threads = std::jthread::hardware_concurrency()) : num_threads_(std::max<std::size_t>(1, num_threads))
    {
        Start();
    }

    void Start(this ThreadPool &self)
    {
        while (self.threads_.size() < self.num_threads_)
        {
            self.threads_.emplace_back([&self]
                {
                    while (!self.stop_.load())
                    {
                        std::function<void()> task;
                        {
                            std::unique_lock lock{ self.cv_mutex_ };
                            self.cv_lock_.wait(lock, [&self]
                                {
                                    return self.stop_.load() || !self.tasks_.empty();
                                });

                            if (self.tasks_.empty())
                                return;
                            task = std::move(self.tasks_.front());
                            self.tasks_.pop();
                        }

                        self.num_threads_ -= 1;
                        task();
                        self.num_threads_ += 1;
                    }
                });
        }
    }

    void Stop(this ThreadPool &self)
    {
        self.stop_.store(true);
        self.cv_lock_.notify_all();

        for (auto &th : self.threads_)
        {
            if (th.joinable())
            {
                std::println(std::cerr, "Join thread: {}", th.get_id());
                th.join();
            }
        }
    }

private:
    std::mutex cv_mutex_;
    std::condition_variable cv_lock_;
    std::atomic_bool stop_{ false };
    std::atomic_size_t num_threads_;
    std::vector<std::jthread> threads_;
    std::queue<std::function<void()>> tasks_;
};
```
