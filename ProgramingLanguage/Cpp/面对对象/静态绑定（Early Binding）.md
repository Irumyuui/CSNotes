# 静态绑定（Early Binding）

使用到多态的时候，在编译期会先对编译期内能确定的这个对象的类型进行绑定。

考虑以下代码，它能编译吗？还是会输出什么？

```cpp
#include <print>

struct Base {
    virtual void Foo(int value = 1) {
        std::println("Base::Foo {}", value);
    }
};
struct Derived : Base {
    void Foo(int value) override {
        std::println("Derived::Foo {}", value);
    }
};

int main() {
    Derived d;
    Base &b = d;
    b.Foo();
}
```

答案是 `Derived::Foo 1` 。因为静态绑定，那么此时编译器会先去找 `Base::Foo` 作为被调用的函数，那么此时 `value` 被默认为 `1` 。但是这里其实是一个多态的调用，也就是到运行时会动态绑定到 `Derived::Foo` ，也就是多态的表现，也就是查了虚表。因此这里会输出 `Derived::Foo 1` 。
