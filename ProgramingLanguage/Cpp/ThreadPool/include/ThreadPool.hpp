#pragma once

#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

#include "Channel.hpp"

#ifndef KARUS_THREAD_POOL_HPP
#define KARUS_THREAD_POOL_HPP

namespace karus {
class ThreadPool {
public:
  using Task = std::function<void()>;

public:
  explicit ThreadPool(std::size_t thread_count);
  ~ThreadPool();

public:
  auto AddTask(const Task &task) -> void;

  template <typename Fn, typename... Args>
    requires requires(Fn fn, Args... args) {
      !std::is_same_v<decltype(fn(args...)), void>;
    }
  auto SubmitTask(Fn &&fn, Args &&...args)
      -> std::future<decltype(fn(args...))>;

  auto AddThread(std::size_t thread_count) -> void;

  auto Stop(bool exec_remain_tasks = true) -> void;

private:
  auto ThreadLoop() -> void;

private:
  Channel<Task> tasks_;
  std::vector<std::thread> threads_;
  std::mutex thread_mutex_;
  std::condition_variable thread_cond_;
  std::mutex wait_tasks_mutex_;
  std::condition_variable wait_tasks_cond_;
  bool is_terminal_{false};
};
} // namespace karus

inline karus::ThreadPool::ThreadPool(std::size_t thread_count) {
  this->threads_.reserve(thread_count);
  while (this->threads_.size() < thread_count) {
    this->threads_.emplace_back([this] { this->ThreadLoop(); });
  }
}

inline karus::ThreadPool::~ThreadPool() { this->Stop(false); }

inline auto karus::ThreadPool::AddTask(const Task &task) -> void {
  this->tasks_.Push(task);
  this->thread_cond_.notify_one();
}

template <typename Fn, typename... Args>
  requires requires(Fn fn, Args... args) {
    !std::is_same_v<decltype(fn(args...)), void>;
  }
auto karus::ThreadPool::SubmitTask(Fn &&fn, Args &&...args)
    -> std::future<decltype(fn(args...))> {
  using RetTy = decltype(fn(args...));
  auto func_ptr = std::make_shared<std::packaged_task<RetTy()>>(
      [fn = std::forward<Fn>(fn),
       args = std::forward_as_tuple(args...)]() -> RetTy {
        return std::apply(fn, args);
      });
  Task task = [func_ptr] { (*func_ptr)(); };
  this->AddTask(task);
  return func_ptr->get_future();
}

inline auto karus::ThreadPool::ThreadLoop() -> void {
  while (true) {
    Task task;
    {
      std::unique_lock lock{this->thread_mutex_};
      if (this->is_terminal_) {
        return;
      }
      if (this->tasks_.Empty()) {
        this->wait_tasks_cond_.notify_one();
        continue;
      }
      this->thread_cond_.wait(lock,
                              [this, &task] { return this->tasks_.Pop(task); });
      if (this->is_terminal_) {
        return;
      }
    }
    task();
  }
}

inline auto karus::ThreadPool::Stop(bool exec_remain_tasks) -> void {
  std::unique_lock lock{this->wait_tasks_mutex_};

  if (exec_remain_tasks) {
    this->wait_tasks_cond_.wait(lock,
                                [this]() { return this->tasks_.Empty(); });
  }

  this->is_terminal_ = true;
  this->thread_cond_.notify_all();
  for (auto &thread : this->threads_) {
    thread.join();
  }

  this->threads_.clear();
  this->is_terminal_ = false;
}

inline auto karus::ThreadPool::AddThread(std::size_t thread_count) -> void {
  for (std::size_t i = 0; i < thread_count; i++) {
    this->threads_.emplace_back([this] { this->ThreadLoop(); });
  }
}

#endif
