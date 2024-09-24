#pragma once

#include <cassert>
#include <clocale>
#include <condition_variable>
#include <cstddef>
#include <functional>
#include <future>
#include <memory>
#include <mutex>
#include <queue>
#include <shared_mutex>
#include <thread>
#include <type_traits>
#include <utility>

namespace Koro {
  
  namespace detail {

    template <typename T> class SafeQueue {
    public:
      SafeQueue() = default;
      ~SafeQueue() = default;

    public:
      bool Empty(this const SafeQueue &self) {
        std::shared_lock lock{self.mutex_};
        return self.que_.empty();
      }

      std::size_t Size(this const SafeQueue &self) {
        std::shared_mutex lock{self.mutex_};
        return self.que_.size();
      }

      void Push(this SafeQueue &self, T &&value) { self.Emplace(std::move(value)); }

      void Push(this SafeQueue &self, const T &value) { self.Emplace(value); }

      template <typename... Ts> void Emplace(this SafeQueue &self, Ts &&...args) {
        std::unique_lock lock{self.mutex_};
        self.que_.emplace(std::forward<Ts>(args)...);
      }

      bool Pop(this SafeQueue &self, T &result) {
        std::unique_lock lock{self.mutex_};
        if (self.que_.empty()) {
          return false;
        }
        result = std::move(self.que_.front());
        self.que_.pop();
        return true;
      }

    private:
      std::queue<T> que_;
      mutable std::shared_mutex mutex_;
    };

  } // namespace detail

  ///
  /// A static thread pool.
  ///
  class ThreadPool {
  public:
    explicit ThreadPool(std::size_t thread_count)
        : thread_count_(thread_count) {
      assert(thread_count > 0);
      work_threads_ = std::make_unique<std::jthread[]>(thread_count);
      for (std::size_t i = 0; i < thread_count_; i++) {
        work_threads_[i] = std::jthread([this] { this->LoopRun(); });
      }
    }

    ThreadPool() : ThreadPool(std::thread::hardware_concurrency()) {}

    ~ThreadPool() {
      Submit([] {}).get();
      is_terminal_ = true;
      cond_.notify_all();
      for (std::size_t i = 0; i < thread_count_; i++) {
        if (work_threads_[i].joinable()) {
          work_threads_[i].join();
        }
      }
    }

    ThreadPool(ThreadPool &&) = delete;
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;

    friend void swap(ThreadPool &, ThreadPool &) = delete;

  public:
    template <typename Fn, typename... Args>
      requires std::is_invocable_v<Fn, Args...>
    auto Submit(this ThreadPool &self, Fn &&fn,
                Args &&...args) -> std::future<decltype(fn(args...))> {
      using ReturnType = decltype(fn(args...));
      std::function func = [&fn, args...] { return fn(args...); };
      auto task_ptr = std::make_shared<std::packaged_task<ReturnType()>>(func);
      std::function<void()> wrapper_func = [task_ptr] { (*task_ptr)(); };

      self.tasks_.Emplace(std::move(wrapper_func));
      self.cond_.notify_one();

      return task_ptr->get_future();
    }

    static ThreadPool* Instance() {
      static ThreadPool pool;
      return std::addressof(pool);
    }

  private:
    void LoopRun(this ThreadPool &self) {
      while (!self.is_terminal_) {
        {
          std::unique_lock lock{self.mutex_};
          if (self.tasks_.Empty()) {
            self.cond_.wait(lock, [&self] {
              return self.is_terminal_ || !self.tasks_.Empty();
            });
            if (self.is_terminal_) {
              break;
            }
          }
          if (std::function<void()> task; self.tasks_.Pop(task)) {
            task();
          }
        }
      }
    }

  private:
    // std::queue<std::function<void()>> tasks_;
    detail::SafeQueue<std::function<void()>> tasks_;
    std::mutex mutex_;
    std::condition_variable cond_;

    std::unique_ptr<std::jthread[]> work_threads_;
    std::size_t thread_count_;
    // std::atomic<bool> is_terminal_{false};
    bool is_terminal_{false};
  };

} // namespace karus
