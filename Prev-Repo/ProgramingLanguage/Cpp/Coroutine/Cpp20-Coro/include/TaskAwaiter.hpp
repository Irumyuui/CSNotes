#pragma once

#include <algorithm>
#include <atomic>
#include <chrono>
#include <concepts>
#include <condition_variable>
#include <coroutine>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <exception>
#include <functional>
#include <future>
#include <list>
#include <mutex>
#include <optional>
#include <thread>
#include <type_traits>
#include <utility>

#include "Executor.hpp"
#include "Result.hpp"

#ifndef KARUS_CORO_TASK_AWAITER_HPP
#define KARUS_CORO_TASK_AWAITER_HPP

namespace karus::coro {

template <typename TResult>
class IAwaiter;

template <typename T, typename TResult>
concept IsAwaiter = std::is_base_of_v<IAwaiter<TResult>, T>;

template <typename TResult>
class IAwaiter {
public:
    using ResultType = TResult;
    
public:
    virtual ~IAwaiter() noexcept = default;

    virtual constexpr bool await_ready() const noexcept {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) {
        handle_ = handle;
        after_suspend();
    }

    TResult await_resume() {
        before_resume();
        return result_->get_or_throw();    
    }

    // set the awaiter's executor
    void set_executor(IExecutor *executor) {
        executor_ = executor;
    }

    // resume the coroutine
    void resume(TResult result) {
        dispatch([this, result] {
            result_ = Result<TResult>(static_cast<TResult>(result));
            handle_.resume();
        });
    }

    void resume() {
        dispatch([this] { handle_.resume(); });
    }

    void resume_exception(std::exception_ptr &&e) {
        dispatch([this, e] {
            result_ = Result<TResult>(std::move(e));
            handle_.resume();
        });
    }

protected:
    virtual void after_suspend() {}

    virtual void before_resume() {}
    
private:
    void dispatch(std::function<void()> &&fn) {
        if (executor_) {
            executor_->execute(std::move(fn));
        } else {
            fn();
        }
    }

protected:
    std::optional<Result<TResult>> result_;

private:
    IExecutor *executor_{nullptr};
    std::coroutine_handle<> handle_{nullptr};
};

template <>
class IAwaiter<void> {
public:
    using ResultType = void;

public:
    virtual ~IAwaiter() noexcept = default;

    virtual constexpr bool await_ready() const noexcept {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) {
        handle_ = handle;
        after_suspend();
    }

    void await_resume() {
        before_resume();
        result_->get_or_throw();
    }

    // set the awaiter's executor
    void set_executor(IExecutor *executor) {
        executor_ = executor;
    }

    // resume the coroutine
    void resume() {
        dispatch([this] { 
            result_ = Result<void>();
            handle_.resume();
        });
    }

    void resume_exception(std::exception_ptr &&e) {
        dispatch([this, e] {
            result_ = Result<void>(static_cast<std::exception_ptr>(e));
            handle_.resume();
        });
    }

protected:
    virtual void after_suspend() {}

    virtual void before_resume() {}
    
private:
    template <typename Fn>
        requires std::is_invocable_r_v<void, Fn>
    void dispatch(Fn &&fn) {
        if (executor_) {
            executor_->execute(std::forward<Fn>(fn));
        } else {
            fn();
        }
    }

protected:
    std::optional<Result<void>> result_;

private:
    IExecutor *executor_{nullptr};
    std::coroutine_handle<> handle_{nullptr};
};

template <typename TResult, IsTExecutor TExecutor>
class Task;

template <typename TResult, IsTExecutor TExecutor>
class TaskAwaiter : public IAwaiter<TResult> {
public:
    explicit TaskAwaiter(Task<TResult, TExecutor> &&task) noexcept
        : task_(std::move(task)) {
    }

    TaskAwaiter(TaskAwaiter &&other) noexcept
        : IAwaiter<TResult>(other), task_(std::move(other.task_)) {
    }

    TaskAwaiter(const TaskAwaiter &) = delete;

    TaskAwaiter& operator=(const TaskAwaiter &other) = delete;

protected:
    void after_suspend() override {
        task_.finally([this] {
            this->resume();
        });
    }

    void before_resume() override {
        if constexpr (std::is_void_v<TResult>) {
            task_.get_result();
            this->result_ = Result<void>();
        } else {
            this->result_ = Result<TResult>(task_.get_result());
        }
    }

private:
    Task<TResult, TExecutor> task_;
};

// dispatch task to different executor 
class DispatchAwaiter {
public:
    explicit DispatchAwaiter(IExecutor *executor) noexcept 
        : executor_(executor) {
    }

    bool await_ready() const { return false; }

    // the coroutine will be managed by the executor
    void await_suspend(std::coroutine_handle<> handle) const {
        executor_->execute([handle] {
            handle.resume();
        });
    }

    void await_resume() {}

private:
    IExecutor *executor_;
};

// coroutine sleep awaiter.
class SleepAwaiter : public IAwaiter<void> {
public:
    explicit SleepAwaiter(std::int64_t duration) noexcept
        : duration_(duration) {
    }

    template <typename Rep, typename Period>
    explicit SleepAwaiter(std::chrono::duration<Rep, Period> &&duration) noexcept
        : duration_(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) {
    }

protected:
    // has a static scheduler menber.
    // the coroutine will be managed by the scheduler
    void after_suspend() override {
        static Scheduler scheduler{};
        scheduler.execute([this] { resume(); }, duration_);
    }

private:
    std::int64_t duration_;
};

template <typename TValue>
class WriteAwaiter;

template <typename TValue>
class ReadAwaiter;

template <typename TValue>
class Channel {
public:
    class ChannelClosedException : std::exception {
    public:
        const char* what() const noexcept override {
            return "CHannel is closed.";
        }
    };

public:
    explicit Channel(std::size_t capcity = 0)
        : buffer_capcity_(capcity) {
        is_active_.store(true, std::memory_order_relaxed);
    }

    Channel(Channel&&) noexcept = delete;
    Channel(const Channel&) = delete;
    Channel& operator=(Channel&&) noexcept = delete;
    Channel& operator=(const Channel&) = delete;

    ~Channel() noexcept {
        try {
            close();
        } catch (...) {
            
        }
    }

public:
    // check the channel is active.
    [[nodiscard]] bool is_active() const noexcept {
        return is_active_.load(std::memory_order_relaxed);
    }

    // check the cahnnel is closed.
    // if the channel is closed, then will throw ChannelClosedException.
    void check_closed() {
        if (!is_active_.load(std::memory_order_relaxed)) {
            throw ChannelClosedException();
        }
    }
    
    // close the channel.
    void close() {
        if (bool except = true; is_active_.compare_exchange_strong(except, false, std::memory_order_relaxed)) {
            clean_up();
        }
    }

    // create WriteAwaiter<TValue> from value.
    // the awaiter will bind this object.
    WriteAwaiter<TValue> write(TValue value) {
        check_closed();
        return WriteAwaiter<TValue>(this, std::move(value));
    }

    WriteAwaiter<TValue> operator << (TValue value) {
        return write(std::move(value));
    }

    // create ReadAwaiter<TValue>.
    // the awaiter will bind this object.
    ReadAwaiter<TValue> read() {
        check_closed();
        return ReadAwaiter<TValue>(this);
    }

    ReadAwaiter<TValue> operator >> (TValue &value) {
        auto reader = read();
        reader.set_value_ptr(&value);
        return reader;
    }

    template <typename TTask>
        requires std::is_same_v<TTask, ReadAwaiter<TValue>> || std::is_same_v<TTask, WriteAwaiter<TValue>>
    void try_push(TTask *task) {
        if constexpr (std::is_same_v<TTask, ReadAwaiter<TValue>>) {
            try_push_reader(task);
        } else if constexpr (std::is_same_v<TTask, WriteAwaiter<TValue>>) {
            try_push_writer(task);
        } else {
            class NotImplementedException : public std::exception {};
            throw NotImplementedException{};
        }
    }

    // if any reader is waiting, then the writer will services for the reader.
    // or try to push value to buffer if the buffer is not full.
    // if the buffer is full, then put the writer in the waiting queue.
    void try_push_writer(WriteAwaiter<TValue> *writer) {
        // static_assert(writer != nullptr, "the writer cannot be nullptr.");
        
        std::unique_lock lock{channel_mutex_};
        check_closed();

        // if is there any reader in the queue, then call resume anyone reader.
        if (!await_reader_queue_.empty()) {
            auto reader = await_reader_queue_.front();
            await_reader_queue_.pop_front();
            lock.unlock();

            // send the writer's value to this reader.
            reader->resume(writer->get_value());
            writer->resume();

            return;
        }

        // if the buffer is not full, then just push the writer's value to the buffer.
        if (buffer_.size() < buffer_capcity_) {
            buffer_.push_back(writer->get_value());
            lock.unlock();

            // resume the writer.
            writer->resume();

            return;
        }

        // await this writer.
        await_writer_queue_.emplace_back(writer);
    }

    // if the buffer is not full, take an value from the buffer and try to replenish it from an await writer.
    // or if the buffer is empty, then will try to get the value from an await writer.
    // if is there are not await writer in the queue, then put the reader in the waiting queue. 
    void try_push_reader(ReadAwaiter<TValue> *reader) {
        // static_assert(reader != nullptr, "the reader cannot be nullptr.");

        std::unique_lock lock{channel_mutex_};

        // if the buffer is not empty, then take a value from buffer.
        if (!buffer_.empty()) {
            auto value = std::move(buffer_.front());
            buffer_.pop_front();

            // now need to resmue a writer.
            // if there is any writer in await status,
            // then get someone value and resume it.
            if (!await_writer_queue_.empty()) {
                auto writer = await_writer_queue_.front();
                await_writer_queue_.pop_front();
                buffer_.emplace_front(writer->get_value());
                lock.unlock();

                writer->resume();
            } else {
                lock.unlock();
            }

            reader->resume(value);

            return;
        }

        // if any of await writer, then resmue it.
        if (!await_writer_queue_.empty()) {
            auto writer = await_writer_queue_.front();
            await_writer_queue_.pop_front();
            buffer_.emplace_front(writer->get_value());
            lock.unlock();

            // resume
            reader->resume(writer->get_value());
            writer->resume();
            return;
        }

        await_reader_queue_.emplace_back(reader);
    }

    template <typename TTask>
        requires std::is_same_v<TTask, ReadAwaiter<TValue>> || std::is_same_v<TTask, WriteAwaiter<TValue>>
    void remove_task(TTask *task) {
        if constexpr (std::is_same_v<TTask, ReadAwaiter<TValue>>) {
            remove_reader(task);
        } else if constexpr (std::is_same_v<TTask, WriteAwaiter<TValue>>) {
            remove_writer(task);
        } else {
            class NotImplementedException : public std::exception {};
            throw NotImplementedException{};
        }
    }

    void remove_reader(ReadAwaiter<TValue> *reader) {
        std::scoped_lock lock{channel_mutex_};
        await_reader_queue_.remove(reader);
    }

    void remove_writer(WriteAwaiter<TValue> *writer) {
        std::scoped_lock loc{channel_mutex_};
        await_writer_queue_.remove(writer);
    }

private:
    // let all await coroutine resume.
    // then clear all task and value on buffer.
    void clean_up() {
        std::scoped_lock lock{channel_mutex_};
        for (auto &writer : await_writer_queue_) {
            writer->resume();
        }
        await_writer_queue_.clear();
        for (auto &reader : await_reader_queue_) {
            reader->resume();
        }
        await_reader_queue_.clear();
        
        buffer_.clear();
    }

private:
    std::size_t buffer_capcity_;
    std::deque<TValue> buffer_;
    std::list<WriteAwaiter<TValue>*> await_writer_queue_;
    std::list<ReadAwaiter<TValue>*> await_reader_queue_;
    std::atomic<bool> is_active_;
    std::mutex channel_mutex_;
    std::condition_variable channel_cond_;
};

// channel's writer
template <typename TValue>
class WriteAwaiter : public IAwaiter<TValue> {
public:
    explicit WriteAwaiter(Channel<TValue> *channel, TValue value)
        : channel_(channel), value_(std::move(value)) {
    }

    WriteAwaiter(WriteAwaiter &&other) noexcept
        : IAwaiter<TValue>(other),
          channel_(std::exchange(other.channel_, nullptr)),
          value_(other.value_) {
    }

    ~WriteAwaiter() noexcept {
        if (channel_) {
            channel_->remove_writer(this);
        }
    }

protected:
    void after_suspend() override {
        channel_->try_push_writer(this);
    }

public:
    TValue get_value() const {
        return value_;
    }

    TValue get_value() {
        return value_;
    }

private:
    Channel<TValue> *channel_;
    TValue value_;
};

// channel reader
template <typename TValue>
class ReadAwaiter : public IAwaiter<TValue> {
public:
    explicit ReadAwaiter(Channel<TValue> *channel)
        : channel_(channel) {
    }

    ReadAwaiter(ReadAwaiter &&other) noexcept
        : IAwaiter<TValue>(other),
          channel_(std::exchange(other.channel_, nullptr)),
          value_ptr_(std::exchange(other.value_ptr_, nullptr)) {
    }

    ~ReadAwaiter() noexcept {
        if (channel_) {
            channel_->remove_reader(this);
        }
    }

public:
    void set_value_ptr(TValue *ptr) noexcept {
        value_ptr_ = ptr;
    }

protected:
    void after_suspend() override {
        channel_->try_push_reader(this);
    }

    void before_resume() override {
        channel_->check_closed();
        if (value_ptr_) {
            *value_ptr_ = this->result_->get_or_throw();
        }
        channel_ = nullptr;
    }

private:
    Channel<TValue> *channel_;
    TValue *value_ptr_{nullptr};
};


template <typename TResult>
class FutureAwait : public IAwaiter<TResult> {
public:
    explicit FutureAwait(std::future<TResult> &&future) noexcept
        : future_(std::move(future)) {
    }

    FutureAwait(FutureAwait &&other) noexcept
        : IAwaiter<TResult>(other), future_(std::move(other.future_)) {
    }

protected:
    void after_suspend() override {
        std::jthread([this] {
            this->resume(this->future_.get());
        }).detach();
    }

private:
    std::future<TResult> future_;
};

} // namespace karus::coro

#endif // KARUS_CORO_TASK_AWAITER_HPP
