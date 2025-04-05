# 实现一个简单的 std::unique_ptr

## 简介

`std::unique_ptr` 是一个独占资源所有权的智能指针，通过 `RAII` 来自动管理资源的构造和析构。

在标准库中，`std::unique_ptr` 的通常实现是具有空基类优化。具体来讲，对于 `std::unique_ptr` 的删除器是其类型中的一部分，如果没有空基类优化，那么 `std::unique_ptr` 所占用的空间将包括至少一个空类的大小。不过这里只是简单实现一个 `unique_ptr` ，不涉及空基类优化的具体实现。

`unique_ptr` 拥有对资源对象的独占所有权，这意味着只能有一个 `unique_ptr` 拥有资源的所有权（换句话说，一个资源的管理只能被一个 `unique_ptr` 托管，多个是不被允许的，但通过一些不合理的行为可以让多个实例共同管理一个）。因为需要确保唯一拥有对象的所有权，因此需要将其拷贝构造函数显示弃置，需要拷贝构造的一个更合理的设计是由类自己提供一个可以拷贝的函数，返回一个 `unique_ptr` 。不过，可以通过移动的方式将资源的所有权转交给另一个 `unique_ptr` ，或者是自己来接管资源。

```cpp
class Foo {
public:
  auto Clone() const -> std::unique_ptr<Foo>;
};
```

要使用 `std::unique_ptr` ，可以通过直接创建一个 `std::unique_ptr` 对象，也可以使用 `std::make_unique` 进行构造。前者的好处是可以自定义删除器，若不需要自定义删除器，则最好使用 `std::make_unique` 。对于 `auto t = std::unique_ptr<T>(new T())` ，这个过程不是异常安全的，当发生异常时，可能导致申请的资源没有被 `std::unique_ptr` 托管，从而发生内存泄露，而使用 `std::make_unique` 则不会。

## 实现一个 unique_ptr

对于一个 `unique_ptr` ，我们只需要让它能够支持移动构造和移动赋值，并需要将拷贝构造和拷贝复制删除，在析构时将资源回收，然后支持释放指针和获取指针，并重载一些裸指针的访问行为即可。要注意的是，需要使用一定的方法，保证删除器是一个可被调用的类型，即使用户实现的无法释放资源，这里使用 `c++20` 的 `concept` 约束模板。

由于这里的实现并没有实现空基类优化，因此需要将裸指针和删除器对象作为成员。

```c++
template <typename Ty, typename Deleter = std::default_delete<Ty>>
  requires std::is_invocable_v<Deleter, Ty *>
class UniquePtr {
public:
  constexpr UniquePtr() noexcept : ptr_(nullptr), deleter_() {}

  constexpr UniquePtr(std::nullptr_t) noexcept : UniquePtr() {}

  explicit UniquePtr(Ty *ptr) noexcept : ptr_(ptr), deleter_() {}

  explicit UniquePtr(Ty *ptr, Deleter &&deleter) noexcept
      : ptr_(ptr), deleter_(std::move(deleter)) {}

  explicit UniquePtr(Ty *ptr, const Deleter &deleter) noexcept
      : ptr_(ptr), deleter_(deleter) {}

  UniquePtr(const UniquePtr &) = delete;

  auto operator=(const UniquePtr &) -> UniquePtr & = delete;

  UniquePtr(UniquePtr &&) noexcept = default;

  auto operator=(UniquePtr &&) noexcept -> UniquePtr & = default;

  ~UniquePtr() noexcept {
    if (this->ptr_ != nullptr) {
      this->deleter_(std::move(this->ptr_));
      this->ptr_ = nullptr;
    }
  }

  auto Release() noexcept -> Ty * {
    this->ptr_ = nullptr;
    return this->ptr_;
  }

  auto Reset(Ty *ptr = nullptr) noexcept -> void {
    if (this->ptr_ != nullptr) {
      this->deleter_(this->ptr_);
    }
    this->ptr_ = ptr;
  }

  auto Swap(UniquePtr &other) noexcept -> void {
    std::swap(this->ptr_, other.ptr_);
    std::swap(this->deleter_, other.deleter_);
  }

  auto Get() const noexcept -> Ty * { return this->ptr_; }

  auto GetDeleter() noexcept -> Deleter & { return this->deleter_; }

  auto GetDeleter() const noexcept -> const Deleter & { return this->deleter_; }

  explicit operator bool() const noexcept { return this->ptr_ != nullptr; }

  auto operator*() const noexcept -> Ty & { return *this->ptr_; }

  auto operator->() const noexcept -> Ty * { return this->ptr_; }

private:
  Ty *ptr_;
  Deleter deleter_;
};
```

接着，还有 `make_unique` 需要被实现。对于 `make_unique` 来说，它需要将传入的参数转发给构造函数，这里也需要约束一下。

```c++
template <typename Ty, typename... Args>
  requires requires(Args &&...args) { new Ty(std::forward<Args>(args)...); }
inline constexpr auto MakeUnique(Args &&...args) -> UniquePtr<Ty> {
  return UniquePtr<Ty>(new Ty(std::forward<Args>(args)...));
}
```

还有一个 `std::unique_ptr<T[]>` 的重载版本，大体是类似的，这里就不实现代码了。
