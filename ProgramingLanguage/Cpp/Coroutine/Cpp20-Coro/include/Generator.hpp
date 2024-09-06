#pragma once

#include <coroutine>
#include <cstddef>
#include <exception>
#include <iterator>
#include <memory>
#include <ranges>
#include <type_traits>
#include <utility>

#ifndef KARSU_CORO_GENERATOR_HPP
#define KARSU_CORO_GENERATOR_HPP

namespace karus::coro {

template <typename Ty>
class Generator {
public:
    using TValue = std::remove_cv_t<Ty>;
    using TRef = std::conditional_t<std::is_reference_v<Ty>, Ty, Ty&>;
    using TPtr = TValue*;
    
public:
    class promise_type {        
    public:
        promise_type() = default;

    public:
        Generator get_return_object() noexcept {
            return Generator { std::coroutine_handle<promise_type>::from_promise(*this) };
        }

        constexpr std::suspend_always initial_suspend() const noexcept {
            return {};
        }

        constexpr std::suspend_always final_suspend() const noexcept {
            return {};
        }

        template <typename T = Ty>
            requires (!std::is_rvalue_reference_v<T>)
        std::suspend_always yield_value(std::remove_reference_t<T>& val) noexcept {
            value_ptr_ = std::addressof(val);
            return {};
        }

        std::suspend_always yield_value(std::remove_reference_t<Ty>&& value) noexcept {
            value_ptr_ = std::addressof(value);
            return {};
        }

        void await_transform() = delete;

        constexpr void return_void() const noexcept {};

        void unhandled_exception() {
            exception_ptr_ = std::current_exception();
        }

        void try_throw() {
            if (exception_ptr_) {
                std::rethrow_exception(exception_ptr_);
            }
        }

        TRef get_value() const {
            return static_cast<TRef>(*value_ptr_);
        }

        TRef get_or_throw() const {
            if (exception_ptr_) {
                std::rethrow_exception(exception_ptr_);
            }
            return static_cast<TRef>(*value_ptr_);
        }

    private:
        TPtr value_ptr_{nullptr};
        std::exception_ptr exception_ptr_{nullptr};
    };

    // generator's iterator
    class iterator {
    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = TValue;
        using pointer = TPtr;
        using reference = TRef;
        using difference_type = std::ptrdiff_t;

    public:
        iterator(std::default_sentinel_t) noexcept : handle_{nullptr} {}

        iterator(const iterator&) = delete;

        iterator& operator=(const iterator&) = delete;

        iterator(iterator &&other) noexcept 
            : handle_(std::exchange(other.handle_, {})) {}

        iterator& operator=(iterator &&other) noexcept {
            handle_ = std::exchange(other.handle_, {});
            return *this;
        }

        [[nodiscard]] TValue& operator*() const noexcept {
            return handle_.promise().get_value();
        }

        [[nodiscard]] iterator& operator++() {
            handle_.resume();
            if (handle_.done()) {
                handle_.promise().try_throw();
            }
            return *this;
        }

        void swap(iterator &other) noexcept {
            std::swap(handle_, other.handle_);
        }
        
        void operator++(int) {
            [[maybe_unused]] auto result = ++ *this;
        }

        friend constexpr bool operator==(const iterator &it, std::default_sentinel_t) noexcept {
            return !it.handle_ || it.handle_.done();
        }

        friend constexpr bool operator==(std::default_sentinel_t, const iterator &it) noexcept {
            return it == std::default_sentinel;
        }

        friend constexpr bool operator!=(const iterator &it, std::default_sentinel_t) noexcept {
            return !(it == std::default_sentinel);
        }

        friend constexpr bool operator!=(std::default_sentinel_t, const iterator &it) noexcept {
            return !(it == std::default_sentinel);
        }

    private:
        template <typename> friend class Generator;
        
        explicit iterator(std::coroutine_handle<promise_type> handle_) noexcept
            : handle_(handle_) {}

    private:
        std::coroutine_handle<promise_type> handle_{nullptr};
    };

public:
    explicit Generator(std::coroutine_handle<promise_type> handle) noexcept
        : handle_(handle) {}

    Generator(const Generator&) = delete;

    Generator(Generator &&other) noexcept
        : handle_(std::exchange(other.handle_, {})) {}

    ~Generator() {
        if (handle_) {
            handle_.destroy();
        }
    }

    Generator& operator=(Generator other) noexcept {
        std::swap(handle_, other.handle_);
        return *this;
    }

public:
    [[nodiscard]] iterator begin() {
        if (handle_) {
            handle_.resume();
            if (handle_.done()) {
                handle_.promise().try_throw();
            }
        }
        return iterator{ handle_ };
    }

    std::default_sentinel_t end() const noexcept {
        return std::default_sentinel;
    }

    template <typename ...Ts>
    [[nodiscard]] static Generator from(Ts &&...args) {
        (co_yield TValue(std::forward<Ts>(args)), ...);
    }

    template <typename TConvertor>
        requires (!std::is_void_v<std::invoke_result_t<TConvertor, TValue>>)
    [[nodiscard]] Generator<std::invoke_result_t<TConvertor, TValue>> select(TConvertor &&fn) {
        for (auto it = begin(); it != end(); ++ it) {
            co_yield fn(*it);
        }
    }

    template <typename TFiller>
        requires std::is_invocable_r_v<bool, TFiller, TValue>
    [[nodiscard]] Generator<TValue> where(TFiller &&fn) {
        for (auto &&item : *this) {
            if (fn(item)) {
                co_yield item;
            }
        }
    }

    template <typename TFn>
        requires std::is_invocable_r_v<void, TFn, TRef>
    [[nodiscard]] Generator<TValue> for_each(TFn &&fn) {
        for (auto &&item : *this) {
            fn(item);
            co_yield item;
        }
    }

    template <typename TContianer>
        requires requires(TContianer cont, TValue value) { cont.push_back(value); }
    [[nodiscard]] TContianer collect() {
        auto result = TContianer{};
        for (auto item : *this) {
            result.push_back(item);
        }
        return result;
    }

    template <std::input_iterator Iter, typename TResult = typename Iter::value_type>
        requires std::is_convertible_v<typename Iter::value_type, TResult>
    [[nodiscard]] static Generator from_iter(Iter begin, Iter end) {
        while (begin != end) {
            co_yield *begin;
            ++ begin;
        }
    }

    [[nodiscard]] static auto from_iter(std::ranges::range auto &&range) {
        return from_iter(std::ranges::begin(range), std::ranges::end(range));
    }

private:
    std::coroutine_handle<promise_type> handle_{nullptr};
};

}

#endif
