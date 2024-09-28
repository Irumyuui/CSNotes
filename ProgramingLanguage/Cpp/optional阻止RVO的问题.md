# optional 阻止 RVO 的问题

在某种程度下，这可能成为性能上的一点开销。

```c++
#include <iostream>
#include <optional>
#include <print>

struct Foo {
    Foo() = default;
    Foo(const Foo&) = default;
    Foo(Foo&&) { std::println("Foo&& constructor called"); }
    Foo& operator=(const Foo&) = default;
    Foo& operator=(Foo&&) {
        std::println("Foo&& operator= called");
        return *this;
    }
    ~Foo() = default;
};

Foo foo() { return Foo{}; }

std::optional<Foo> foo2() { return Foo{}; }

int main() {
    auto f1 = foo();  // 啥都不输出
    auto f2 = foo2(); // 输出 "Foo&& constructor called"
}
```
