# CRTP

Curiously Recurring Template Pattern, 中文名字叫作**奇异的模板递归**什么的。

这个是用来做什么的呢？可以**实现编译期多态**。

## 运行时多态

我们先考虑一下运行时多态是怎么实现的。如果需要实现多态，那么使用虚函数是一种很好的解决手段，不过，为什么说它是运行时的多态呢？考虑函数调用的时候是如何找到对应的虚函数的？编译时为每个类生成独特的虚函数表，并在实例对象的首地址放着一个指向虚函数表的指针，当调用对应虚函数时，此时会查找虚函数表以确定正确的虚函数版本，但这在一定程度上导致了运行时的开销。

```c++
struct Base {
    virtual ~Base() {}
    virtual void Dump() {
        std::cout << "Base::Dump" << '\n';
    }
};
struct A : public Base {
    void Dump() override {
        std::cout << "A::Dump" << '\n';
    }
};
struct B : public Base {
    void Dump() override {
        std::cout << "B::Dump" << '\n';
    }
};

int main() {
    std::unique_ptr<Base> a = std::make_unique<A>();
    std::unique_ptr<Base> b = std::make_unique<B>();

    a->Dump();  // A::Dump
    b->Dump();  // B::Dump
}
```

## CRTP 实现编译期多态

我们再来考虑一下如果使用了 CRTP 后，多态要怎么实现？

基类通过模板，获取派生类的类型，然后通过 `static_cast` 转换为派生类的指针，调用派生类的实现函数，最后就在编译期中确定好类型了，优化掉虚函数的开销。

```c++
template <typename Derived>
struct Base {
    void Dump() {
        static_cast<Derived*>(this)->DumpImpl();
    }
};
struct A : public Base<A> {
    void DumpImpl() {
        std::cout << "A::Dump" << '\n';
    }
};
struct B : public Base<B> {
    void DumpImpl() {
        std::cout << "B::Dump" << '\n';
    }
};

int main() {
    std::unique_ptr<A> a = std::make_unique<A>();
    std::unique_ptr<B> b = std::make_unique<B>();

    a->Dump();  // A::Dump
    b->Dump();  // B::Dump
}
```

## 更好的 CRTP：推导 this

到了 `c++23` ，就不再直接需要使用 `CRTP` 了，而是使用推导 `this` 会更好。
