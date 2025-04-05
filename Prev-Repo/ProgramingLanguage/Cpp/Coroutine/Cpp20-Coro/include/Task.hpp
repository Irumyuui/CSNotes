#pragma once

#include <chrono>
#include <condition_variable>
#include <coroutine>
#include <deque>
#include <exception>
#include <functional>
#include <mutex>
#include <type_traits>
#include <utility>

#include "Executor.hpp"
#include "Result.hpp"
#include "TaskAwaiter.hpp"

#ifndef KARUS_CORO_TASK_HPP
#define KARUS_CORO_TASK_HPP

namespace karus::coro {

template <typename TResult, IsTExecutor TExecutor>
class TaskPromise;

template <IsTExecutor TExecutor>
class TaskPromise<void, TExecutor>;

template <typename TResult, IsTExecutor TExecutor>
class Task;

template <IsTExecutor TExecutor>
class Task<void, TExecutor>;

// a task which will contain a result.
template <typename TResult, IsTExecutor TExecutor = NoopExecutor>
class Task {
public:
    using promise_type = TaskPromise<TResult, TExecutor>;

public:
    explicit Task(std::coroutine_handle<promise_type> handle) noexcept;
    Task(Task &&task) noexcept;
    Task(const Task&) = delete;
    Task& operator=(Task &) = delete;
    ~Task() noexcept;

public:
    TResult get_result();

public:
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, TResult>
    Task& then(Fn &&fn);

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, std::exception&>
    Task& catching(Fn &&fn);

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
    Task& finally(Fn &&fn);

private:
    std::coroutine_handle<promise_type> handle_;
};

// a task without value.
template <IsTExecutor TExecutor>
class Task<void, TExecutor> {
public:
    using promise_type = TaskPromise<void, TExecutor>;

public:
    explicit Task(std::coroutine_handle<promise_type> handle) noexcept;
    Task(Task &&task) noexcept;
    Task(const Task&) = delete;
    Task& operator=(Task &) = delete;
    ~Task() noexcept;

public:
    void get_result();

public:
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
    Task& then(Fn &&fn);

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, std::exception&>
    Task& catching(Fn &&fn);

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
    Task& finally(Fn &&fn);

private:
    std::coroutine_handle<promise_type> handle_;
};

// Task<TResult> 's promise_type
template <typename TResult, IsTExecutor TExecutor>
class TaskPromise {
public:
    DispatchAwaiter initial_suspend();
    std::suspend_always final_suspend() noexcept;
    Task<TResult, TExecutor> get_return_object();
    void unhandled_exception();
    void return_value(TResult value);
    TResult get_result();

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, Result<TResult>>
    void on_completed(Fn &&fn);

public:
    template <typename TAwaiter>
        requires IsAwaiter<TAwaiter, typename TAwaiter::ResultType>
    TAwaiter await_transform(TAwaiter awaiter) {
        awaiter.set_executor(&executor_);
        return awaiter;
    }

    template <typename TRet, IsTExecutor TExec>
    TaskAwaiter<TRet, TExec> await_transform(Task<TRet, TExec> &&task) {
        return await_transform(TaskAwaiter<TRet, TExec>(std::move(task)));
    }

private:
    void notify_callbacks();

private:
    std::deque<std::function<void(Result<TResult>)>> callbacks_;
    std::optional<Result<TResult>> result_;
    std::mutex mutex_;
    std::condition_variable cond_;
    TExecutor executor_;
};

// Task<TResult> 's promise_type
template <IsTExecutor TExecutor>
class TaskPromise<void, TExecutor> {
public:
    DispatchAwaiter initial_suspend();
    std::suspend_always final_suspend() noexcept;
    Task<void, TExecutor> get_return_object();
    void unhandled_exception();
    void return_void();
    void get_result();

    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, Result<void>>
    void on_completed(Fn &&fn);
    
public:
    template <typename TAwaiter>
        requires IsAwaiter<TAwaiter, typename TAwaiter::ResultType>
    TAwaiter await_transform(TAwaiter awaiter) {
        awaiter.set_executor(&executor_);
        return awaiter;
    }

    template <typename TRet, IsTExecutor TExec>
    TaskAwaiter<TRet, TExec> await_transform(Task<TRet, TExec> &&task) {
        return await_transform(TaskAwaiter<TRet, TExec>(std::move(task)));
    }
    
private:
    void notify_callbacks();

private:
    std::deque<std::function<void(Result<void>)>> callbacks_;
    std::optional<Result<void>> result_;
    std::mutex mutex_;
    std::condition_variable cond_;
    TExecutor executor_;
};

/*
 * class Task<TResult>;
 */

template <typename TResult, IsTExecutor TExecutor>
Task<TResult, TExecutor>::Task(std::coroutine_handle<promise_type> handle) noexcept
    : handle_(handle) {
}

template <typename TResult, IsTExecutor TExecutor>
Task<TResult, TExecutor>::Task(Task &&task) noexcept
    : handle_(std::exchange(task.handle_, {})) {
}

template <typename TResult, IsTExecutor TExecutor>
Task<TResult, TExecutor>::~Task() noexcept {
    if (handle_)
        handle_.destroy();
}

template <typename TResult, IsTExecutor TExecutor>
TResult Task<TResult, TExecutor>::get_result() {
    return handle_.promise().get_result();
}

// accepts a callback function that handles asynchronous return values
template <typename TResult, IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, TResult>
Task<TResult, TExecutor>& Task<TResult, TExecutor>::then(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto result) {
        try {
            fn(result.get_or_throw());
        } catch (...) {

        }
    });
    return *this;
}

// accepts a callback function that handles exceptions in asynchronous
template <typename TResult, IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, std::exception&>
Task<TResult, TExecutor>& Task<TResult, TExecutor>::catching(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto result) {
        try {
            result.get_or_throw();
        } catch (std::exception &e) {
            fn(e);
        }
    });
    return *this;
}

// accepts a callback function that just work.
template <typename TResult, IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
Task<TResult, TExecutor>& Task<TResult, TExecutor>::finally(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto) {
        fn();
    });
    return *this;
}

/*
 * class Task<void>;
 */

template <IsTExecutor TExecutor>
inline Task<void, TExecutor>::Task(std::coroutine_handle<promise_type> handle) noexcept
    : handle_(handle) {
}

template <IsTExecutor TExecutor>
inline Task<void, TExecutor>::Task(Task &&task) noexcept
: handle_(std::exchange(task.handle_, {})) {
}

template <IsTExecutor TExecutor>
inline Task<void, TExecutor>::~Task() noexcept {
    if (handle_)
        handle_.destroy();
}

template <IsTExecutor TExecutor>
inline void Task<void, TExecutor>::get_result() {
    handle_.promise().get_result();
}

template <IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
inline Task<void, TExecutor>& Task<void, TExecutor>::then(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto result) {
        try {
            result.get_or_throw();
            fn();
        } catch (...) {

        }
    });
    return *this;
}

template <IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, std::exception&>
inline Task<void, TExecutor>& Task<void, TExecutor>::catching(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto result) {
        try {
            result.get_or_throw();
        } catch (std::exception &e) {
            fn(e);
        }
    });
    return *this;
}

template <IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
inline Task<void, TExecutor>& Task<void, TExecutor>::finally(Fn &&fn) {
    handle_.promise().on_completed([fn = std::forward<Fn>(fn)](auto) {
        fn();
    });
    return *this;
}

/*
 * class TaskPromise<TResult>
 */

template <typename TResult, IsTExecutor TExecutor>
DispatchAwaiter TaskPromise<TResult, TExecutor>::initial_suspend() {
    return DispatchAwaiter{ &executor_ };
}

template <typename TResult, IsTExecutor TExecutor>
std::suspend_always TaskPromise<TResult, TExecutor>::final_suspend() noexcept {
    return {};
}

template <typename TResult, IsTExecutor TExecutor>
Task<TResult, TExecutor> TaskPromise<TResult, TExecutor>::get_return_object() {
    return Task {
        std::coroutine_handle<TaskPromise>::from_promise(*this)
    };
}

template <typename TResult, IsTExecutor TExecutor>
void TaskPromise<TResult, TExecutor>::unhandled_exception() {
    std::scoped_lock lock{mutex_};
    result_ = Result<TResult>(std::current_exception());
    cond_.notify_all();
    notify_callbacks();
}

template <typename TResult, IsTExecutor TExecutor>
void TaskPromise<TResult, TExecutor>::return_value(TResult value) {
    std::scoped_lock lock{mutex_};
    result_ = Result<TResult>(std::move(value));
    cond_.notify_all();
    notify_callbacks();
}

template <typename TResult, IsTExecutor TExecutor>
TResult TaskPromise<TResult, TExecutor>::get_result() {
    std::unique_lock lock{mutex_};
    if (!result_.has_value()) 
        cond_.wait(lock);
    return result_->get_or_throw();
}

template <typename TResult, IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, Result<TResult>>
void TaskPromise<TResult, TExecutor>::on_completed(Fn &&fn) {
    std::unique_lock lock{mutex_};
    if (result_.has_value()) {
        auto value = result_.value();
        lock.unlock();
        fn(value);
    } else {
        callbacks_.emplace_back(std::forward<Fn>(fn));
    }
}

template <typename TResult, IsTExecutor TExecutor>
void TaskPromise<TResult, TExecutor>::notify_callbacks() {
    for (auto value = result_.value(); auto &&callback : callbacks_)
        callback(value);
    callbacks_.clear();
}

/*
 * class TaskPromise<void>;
 */
template <IsTExecutor TExecutor>
inline DispatchAwaiter TaskPromise<void, TExecutor>::initial_suspend() {
    return DispatchAwaiter{ &executor_ };
}

template <IsTExecutor TExecutor>
inline std::suspend_always TaskPromise<void, TExecutor>::final_suspend() noexcept {
    return {};
}

template <IsTExecutor TExecutor>
inline Task<void, TExecutor> TaskPromise<void, TExecutor>::get_return_object() {
    return Task {
        std::coroutine_handle<TaskPromise>::from_promise(*this)
    };
}

template <IsTExecutor TExecutor>
inline void TaskPromise<void, TExecutor>::unhandled_exception() {
    std::scoped_lock lock{mutex_};
    result_ = Result<void>(std::current_exception());
    cond_.notify_all();
    notify_callbacks();
}

template <IsTExecutor TExecutor>
inline void TaskPromise<void, TExecutor>::return_void() {
    std::scoped_lock lock{mutex_};
    result_ = Result<void>();
    cond_.notify_all();
    notify_callbacks();
}

template <IsTExecutor TExecutor>
inline void TaskPromise<void, TExecutor>::get_result() {
    std::unique_lock lock{mutex_};
    if (!result_.has_value()) 
        cond_.wait(lock);
    return result_->get_or_throw();
}

template <IsTExecutor TExecutor>
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn, Result<void>>
inline void TaskPromise<void, TExecutor>::on_completed(Fn &&fn) {
    std::unique_lock lock{mutex_};
    if (result_.has_value()) {
        auto value = result_.value();
        lock.unlock();
        fn(value);
    } else {
        callbacks_.emplace_back(std::forward<Fn>(fn));
    }
}

template <IsTExecutor TExecutor>
inline void TaskPromise<void, TExecutor>::notify_callbacks() {
    for (auto value = result_.value(); auto &&callback : callbacks_)
        callback(value);
    callbacks_.clear();
}

} // namespace karus::coro

#endif // KARUS_CORO_TASK_HPP
