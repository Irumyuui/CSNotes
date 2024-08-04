# 基础 Allocator

从 `c++20` 开始，最基础的 allocator 只需要以下类型和成员方法即可实现一个。

```c++
#include <cstddef>
#include <iostream>
#include <ostream>
#include <print>
#include <vector>

template <typename T>
struct Allocator
{
    using value_type = T;
    using size_type = std::size_t;
    using different_type = std::ptrdiff_t;

    constexpr auto allocate(size_type n) -> T*
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    constexpr void deallocate(T* p, [[maybe_unused]] size_type n)
    {
        ::operator delete(p);
    }
};

int main() {
    std::vector<int, Allocator<int>> a{1, 2, 3};
    for (auto x : a) {
        std::cout << x << ' ';
    }
    std::cout << '\n';
}
```