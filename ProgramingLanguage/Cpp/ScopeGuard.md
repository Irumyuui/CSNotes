# ScopeGuard

```cpp
template <typename TInvocable, typename ...TArgs>
    requires std::invocable<TInvocable, TArgs...>
class ScopeGuard
{
private:
    TInvocable invocable_;
    std::tuple<TArgs...> args_;

public:
    template <typename Invocable, typename ...Args>
        requires std::invocable<Invocable, Args...>
    constexpr ScopeGuard(Invocable &&invocable, Args &&...args) : invocable_(std::forward<Invocable>(invocable)), args_{std::forward<Args>(args)...}
    {
    }

    constexpr ScopeGuard(const ScopeGuard&) = delete;

    constexpr ~ScopeGuard() {
        std::apply(invocable_, args_);
    }
};

template <typename Invocable, typename ...Args>
ScopeGuard(Invocable &&invocable, Args &&...args) -> ScopeGuard<Invocable, Args...>;

int main()
{
    auto fn1 = [](this auto &&self) { std::println("{}", (uint64_t)(std::addressof(self))); };
    ScopeGuard g1 = fn1;  // 生命周期同一个

    // 生命周期不同
    auto fn2 = std::make_unique<std::function<void()>>([](this auto &&self) { std::println("{}", (uint64_t)(std::addressof(self))); });
    auto fn3 = std::make_unique<std::function<void()>>(*fn2);

    ScopeGuard g2 = [fn = std::move(fn2)] { (*fn)(); };
    ScopeGuard g3 = [fn = std::move(fn3)] { (*fn)(); };
}
```