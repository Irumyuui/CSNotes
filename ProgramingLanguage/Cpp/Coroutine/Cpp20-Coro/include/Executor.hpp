#pragma once

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>

#ifndef KARUS_CORO_EXECUTOR_HPP
#define KARUS_CORO_EXECUTOR_HPP

namespace karus::coro {

// the interface of executor.
class IExecutor {
public:
    virtual ~IExecutor() noexcept = default;
    virtual void execute(std::function<void()> &&fn) = 0;
};

// check the type is derived from IExecutor.
template <typename T>
concept IsTExecutor = std::is_base_of_v<IExecutor, T> && !std::is_same_v<T, IExecutor>;

// the executor just run the coroutine on current thread.
class NoopExecutor : public IExecutor {
public:
    void execute(std::function<void()> &&fn) override {
        fn();
    }
};

// the executor will start a new thread to run the coroutine.
class NewThreadExecutor : public IExecutor {
public:
    void execute(std::function<void()> &&fn) override {
        std::jthread(fn).detach();
    }
};

// the executor will use std::async to run the coroutine.
class AsyncExecutor : public IExecutor {
public:
    void execute(std::function<void()> &&fn) override {
        [[maybe_unused]] auto result = std::async(fn);
    }
};

// the executor has a thread pool, coroutines maybe on different thread.
class LooperExecutor : public IExecutor {
public:
    LooperExecutor() {
        is_active_.store(true, std::memory_order_relaxed);
        // work_threads_ = std::jthread([this] {
        //     this->run_loop();
        // });
        work_threads_ = std::make_unique<std::jthread[]>(std::jthread::hardware_concurrency());
        for (std::size_t i = 0; i < std::jthread::hardware_concurrency(); i ++) {
            work_threads_[i] = std::jthread([this] {
                this->run_loop();
            });
        }
    }

    ~LooperExecutor() noexcept override {
        try {
            shutdown(false);
            join();
        } catch (...) {

        }
    }

public:
    void execute(std::function<void()> &&fn) override {
        std::unique_lock lock{mutex_};
        if (is_active_.load(std::memory_order_relaxed)) {
            tasks_.emplace_back(std::move(fn));
            lock.unlock();
            cond_.notify_one();
        }
    }

    void shutdown(bool wait_for_complete = true) {
        is_active_.store(false, std::memory_order_relaxed);
        if (!wait_for_complete) {
            std::scoped_lock lock{mutex_};
            tasks_.clear();
        }

        cond_.notify_all();
    }

    void join() {
        for (std::size_t i = 0; i < std::jthread::hardware_concurrency(); i ++) {
            if (work_threads_[i].joinable()) {
                work_threads_[i].join();
            }
        }
    }
    

private:
    void run_loop() {
        while (is_active_.load(std::memory_order_relaxed) || !tasks_.empty()) {
            std::unique_lock lock{mutex_};
            if(tasks_.empty()) {
                cond_.wait(lock);
                if (tasks_.empty())  {
                    continue;
                }
            }

            auto fn = std::move(tasks_.front());
            tasks_.pop_front();
            lock.unlock();
            fn();
        }
    }

private:
    std::mutex mutex_;
    std::condition_variable cond_;
    std::deque<std::function<void()>> tasks_;
    std::atomic<bool> is_active_;
    // std::jthread work_thread_;
    std::unique_ptr<std::jthread[]> work_threads_;
};

// this executor is LooperExecutor's wapper, it will execute coroutines using a static looper executor.
class SharedLooperExecutor : public IExecutor {
public:
    void execute(std::function<void()> &&fn) override {
        static LooperExecutor executor{};
        executor.execute(std::move(fn));
    }
};

// to impl delay taks
class DelayedExecutable {
public:
    explicit DelayedExecutable(std::function<void()> &&fn, std::int64_t delay)
        : fn_(std::move(fn)) {
        auto current_time 
            = std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
            ).count();
        scheduled_time_ = current_time + delay;
    }

    std::int64_t delay() const {
        return scheduled_time_ 
            - std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::system_clock::now().time_since_epoch()
              ).count();
    }

    std::int64_t get_sheduled_time() const noexcept {
        return scheduled_time_;
    }

    void operator() () {
        fn_();
    }

    void operator() () const {
        fn_();
    }

    constexpr auto operator <=> (const DelayedExecutable &rhs) const noexcept {
        return scheduled_time_ <=> rhs.scheduled_time_;
    }

private:
    std::function<void()> fn_;
    std::int64_t scheduled_time_;
};

// a delay task's scheduler
class Scheduler {
public:
    Scheduler() {
        is_active_.store(true, std::memory_order_relaxed);
        work_thread_ = std::jthread([this] {
            this->run_loop();
        });
    }
    
    ~Scheduler() noexcept {
        try {
            shotdown(false);
            join();
        } catch (...) {

        }
    }

public:
    void join() {
        if (work_thread_.joinable()) {
            work_thread_.join();
        }
    }

    void shotdown(bool wait_for_complete = true) {
        is_active_.store(false, std::memory_order_relaxed);
        if (!wait_for_complete) {
            std::scoped_lock lock{mutex_};
            decltype(delay_tasks_)().swap(delay_tasks_);
        }
        cond_.notify_all();
    }

    void execute(std::function<void()> &&fn, std::int64_t delay) {
        delay = std::max<std::int64_t>(delay, 0);
        std::unique_lock lock{mutex_};
        
        if (!is_active_.load(std::memory_order_relaxed))
            return;
        
        auto is_need_nodify_one = delay_tasks_.empty() || delay_tasks_.top().delay() > delay;
        delay_tasks_.emplace(std::move(fn), delay);
        lock.unlock();
        
        if (is_need_nodify_one) 
            cond_.notify_one();
    }

private:
    void run_loop() {
        while (is_active_.load(std::memory_order_relaxed) || !delay_tasks_.empty()) {
            std::unique_lock lock{mutex_};
            if (delay_tasks_.empty()) {
                cond_.wait(lock);
            }
            if (delay_tasks_.empty()) {
                continue;
            }

            auto executable = delay_tasks_.top();
            if (auto delay = executable.delay(); delay > 0) {
                auto status = cond_.wait_for(lock, std::chrono::milliseconds(delay));
                if (status != std::cv_status::timeout) {
                    continue;
                }
            }
            delay_tasks_.pop();
            lock.unlock();

            executable();
        }
    }

private:
    std::priority_queue<DelayedExecutable, std::vector<DelayedExecutable>, std::greater<DelayedExecutable>> delay_tasks_;
    std::mutex mutex_;
    std::condition_variable cond_;
    std::atomic<bool> is_active_;
    std::jthread work_thread_;
};

}

#endif  // KARUS_CORO_EXECUTOR_HPP
