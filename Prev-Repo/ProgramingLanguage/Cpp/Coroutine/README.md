# Coroutine

```c++
#include <coroutine>
#include <iostream>

struct task {
    struct promise_type {
        task get_return_object() {
            return task {
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }

        constexpr auto initial_suspend() { return std::suspend_never{}; }
        constexpr auto final_suspend() noexcept { return std::suspend_never{}; }
        constexpr void return_void() {}
        void unhandled_exception() {}
    };
    std::coroutine_handle<promise_type> _coroutine = nullptr;

    constexpr task() = default;
    constexpr task(task const &) = delete;
    constexpr task &operator=(task const &) = delete;

    constexpr task(task &&other) : _coroutine(other._coroutine) {
        other._coroutine = nullptr;
    }

    constexpr task &operator=(task &&other) {
        if (&other != this) {
            _coroutine = other._coroutine;
            other._coroutine = nullptr;
        }
        return *this;
    }
    constexpr explicit task(std::coroutine_handle<promise_type> coroutine)
        : _coroutine(coroutine) {}
    
    ~task() {
        if (_coroutine) {
            _coroutine.destroy();
        }
    }
    
    void resume() { _coroutine.resume(); }
};

task counter() {
    std::cout << "counter: called\n";
    for (int i = 1;; i++) {
        co_await std::suspend_always{};
        std::cout << "counter:: resumed (#" << i << ")\n";
    }
}

int main() {
    std::cout << "main:    calling counter\n";
    auto t = counter();
    std::cout << "main:    resuming counter\n";
    t.resume();
    t.resume();
    t.resume();
    t.resume();
    t.resume();
    std::cout << "main:    done\n";
    return 0;
}
```