#include <mutex>
#include <print>
#include <shared_mutex>
#include <thread>

class SharedMutex
{
  private:
    std::mutex mutex_;
    std::condition_variable gate1_;
    std::condition_variable gate2_;
    unsigned state_{};

    static constexpr unsigned s_write_entered_ = 1U << (sizeof(unsigned) * __CHAR_BIT__ - 1);
    static constexpr unsigned s_readers_ = ~s_write_entered_;

  public:
    SharedMutex() = default;
    SharedMutex(const SharedMutex &) = delete;
    SharedMutex &operator=(const SharedMutex &) = delete;

  public:
    void lock()
    {
        std::unique_lock lock{mutex_};
        while (state_ & s_write_entered_)
            gate1_.wait(lock);

        state_ |= s_write_entered_;

        while (state_ & s_readers_)
            gate2_.wait(lock);
    }

    void unlock()
    {
        std::lock_guard lock{mutex_};
        state_ = 0;
        gate1_.notify_all();
    }

    bool try_lock()
    {
        std::unique_lock lock{mutex_};
        if (state_ == 0)
        {
            state_ = s_write_entered_;
            return true;
        }
        return false;
    }

    void lock_shared()
    {
        std::unique_lock lock{mutex_};
        while ((state_ & s_write_entered_) || (state_ & s_readers_) == s_readers_)
            gate1_.wait(lock);
        // 取低位，然后 +1
        auto num_readers = (state_ & s_readers_) + 1;
        state_ &= ~s_readers_;
        state_ |= num_readers;
    }

    void unlock_shared()
    {
        std::lock_guard lock{mutex_};
        auto num_readers = (state_ & s_readers_) - 1;
        state_ &= ~s_readers_;
        state_ |= num_readers;
        if (state_ & s_write_entered_)
        {
            if (num_readers == 0)
                gate2_.notify_one();
        }
        else
        {
            if (num_readers == s_readers_ - 1)
                gate1_.notify_one();
        }
    }

    bool try_lock_shared()
    {
        std::unique_lock lock{mutex_};
        auto num_readers = state_ & s_readers_;
        // 是否被其他线程排他占用 && 是否共享占有的线程达到上限
        if (!(state_ & s_write_entered_) && num_readers != s_readers_)
        {
            num_readers += 1;
            state_ &= ~s_readers_;
            state_ |= num_readers;
            return true;
        }
        return false;
    }
};

int main()
{
    auto mutex = SharedMutex();
    int tick = 0;

    auto t1 = std::jthread([&] {
        while (true)
        {
            {
                std::shared_lock lock{mutex};
                std::println("t1 read: {}", tick);
            }
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);
        }
    });

    auto t2 = std::jthread([&] {
        while (true)
        {
            {
                std::shared_lock lock{mutex};
                std::println("t2 read: {}", tick);
            }
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);
        }
    });

    auto t3 = std::jthread([&] {
        while (true)
        {
            {
                std::unique_lock lock{mutex};
                std::println("t3 write: {}", ++tick);
            }
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(50ms);
        }
    });

    t1.join();
    t2.join();
    t3.join();
}