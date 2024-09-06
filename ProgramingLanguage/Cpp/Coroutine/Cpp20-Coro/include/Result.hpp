#pragma once

#include <exception>
#ifndef KARUS_CORO_RESULT_HPP
#define KARUS_CORO_RESULT_HPP

namespace karus::coro {

// task result with value
template <typename TResult>
class Result {
public:
    Result() = default;
    
    explicit Result(TResult &&value) noexcept
        : value_(std::move(value)) {};

    explicit Result(std::exception_ptr &&e_ptr) noexcept
        : e_ptr_(std::move(e_ptr)) {}

    // when an exception exists, rethrow the exception, otherwise get the value
    TResult get_or_throw() {
        if (e_ptr_)
            std::rethrow_exception(e_ptr_);
        return value_;
    }

private:
    TResult value_;
    std::exception_ptr e_ptr_;
};

// task result without value
template <>
class Result<void> {
public:
    Result() = default;

    explicit Result(std::exception_ptr &&e_ptr) noexcept
        : e_ptr_(std::move(e_ptr)) {}

    // when an exception exists, rethrow the exception, or just return
    void get_or_throw() {
        if (e_ptr_)
            std::rethrow_exception(e_ptr_);
    }

private:
    std::exception_ptr e_ptr_;
};

} // namespace karus::coro

#endif // KARUS_CORO_RESULT_HPP
