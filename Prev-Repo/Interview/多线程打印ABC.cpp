#include <mutex>
#include <print>
#include <thread>

int main()
{
    std::mutex mutex;
    std::condition_variable cond;
    int state = 0;

    auto t1 = std::jthread([&] {
        while (true)
        {
            std::unique_lock lock{mutex};
            cond.wait(lock, [&] -> bool { return state == 0; });
            std::println("A");
            (state += 1) %= 3;
            cond.notify_all();
        }
    });
    auto t2 = std::jthread([&] {
        while (true)
        {
            std::unique_lock lock{mutex};
            cond.wait(lock, [&] -> bool { return state == 1; });
            std::println("B");
            (state += 1) %= 3;
            cond.notify_all();
        }
    });
    auto t3 = std::jthread([&] {
        while (true)
        {
            std::unique_lock lock{mutex};
            cond.wait(lock, [&] -> bool { return state == 2; });
            std::println("C");
            (state += 1) %= 3;
            cond.notify_all();
        }
    });

    t1.join();
    t2.join();
    t3.join();
}