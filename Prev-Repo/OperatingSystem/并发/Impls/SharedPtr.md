# SharedPtr

省流版

```c++
#include <atomic>
#include <print>
#include <utility>

template <typename T>
class SharedPtr {
private:
    using Self = SharedPtr;

    struct RefPtrCounter {
        std::atomic_size_t ref_count;
        T* ptr;
    };
    RefPtrCounter* data_;

public:
    explicit SharedPtr(T* ptr) : data_(new RefPtrCounter{1, ptr}) {}

    ~SharedPtr() {
        if (data_ && --data_->ref_count == 0) {
            if (data_->ptr) {
                delete data_->ptr;
            }
            delete data_;
        }
    }

    SharedPtr(const Self& other) : data_(other.data_) {
        if (data_) {
            ++data_->ref_count;
        }
    }

    SharedPtr(Self&& other) noexcept : data_(std::exchange(other.data_, nullptr)) {
    }

    SharedPtr& operator=(this Self &self, Self other) {
        std::swap(self.data_, other.data_);
        return self;
    }
    
    const T& operator*(this const Self &self) {
        return *self->ptr;
    }

    T& operator*(this Self &self) {
        return *self.data_->ptr;
    }

    const T* operator->(this const Self &self) {
        return self.data_->ptr;
    }

    T* operator->(this Self &self) {
        return self.data_->ptr;
    }

    constexpr operator bool(this const Self &self) noexcept {
        return static_cast<bool>(self.data_);
    }

    void reset(this Self &self, T* ptr = nullptr) {
        auto new_sptr = Self(ptr);
        self.swap(new_sptr);
    }

    void swap(this Self &self, Self& other) noexcept {
        std::swap(self.data_, other.data_);
    }
};

template <typename T, typename ...Ts>
    requires std::is_constructible_v<T, Ts...>
SharedPtr<T> make_shared(Ts&&... args) {
    return SharedPtr<T>(new T(std::forward<Ts>(args)...));
}

int main() {
    auto a = make_shared<int>(10);
    auto b = a;
    auto c = std::move(b);

    *c = 1;

    if (a) {
        std::println("a = {}", *a);
    } else {
        std::println("a is null");
    }
    if (b) {
        std::println("b = {}", *b);
    } else {
        std::println("b is null");
    }
    if (c) {
        std::println("c = {}", *c);
    } else {
        std::println("c is null");
    }

    c.reset(new int(30));
    b.reset(new int(114));

    if (a) {
        std::println("a = {}", *a);
    } else {
        std::println("a is null");
    }
    if (b) {
        std::println("b = {}", *b);
    } else {
        std::println("b is null");
    }
    if (c) {
        std::println("c = {}", *c);
    } else {
        std::println("c is null");
    }
}
```

全部版

```c++
#pragma once

#include "Utility.hpp"
#include <atomic>
#include <cstddef>
#include <type_traits>
#include <utility>

namespace tystl {

template <typename T>
class SharedPtr;

template <typename T>
class WeakPtr;

template <typename T>
class EnableSharedFromThis;

template <typename T>
constexpr bool CanEnableShared = std::is_base_of_v<EnableSharedFromThis<T>, T>;

template <typename T>
class RefCount {
public:
  constexpr explicit RefCount(T* ptr) noexcept : ptr_(ptr) {}
  
  constexpr void AddRef() noexcept {
    use_ref_ ++;
  }

  constexpr void SubRef() noexcept {
    if ((-- use_ref_) == 0) {
      DestroyResource();
      SubWRef();
    }
  }

  constexpr void AddWRef() noexcept {
    weak_ref_ ++;
  }

  constexpr void SubWRef() noexcept {
    if ((-- weak_ref_) == 0) {
      DeleteThis();
    }
  }

  constexpr bool TryAddRef() noexcept {
    if (use_ref_ == 0) {
      return false;
    }
    use_ref_ += 1;
    return true;
  }

  constexpr void DestroyResource() noexcept {
    delete ptr_;
  }

  constexpr void DeleteThis() noexcept {
    delete this;
  }

  constexpr std::size_t UseCount() const noexcept {
    return use_ref_;
  }

  [[nodiscard]]
  constexpr T* Get() const noexcept {
    return ptr_;
  }

private:
  std::atomic_size_t use_ref_{1};
  std::atomic_size_t weak_ref_{1};
  T* ptr_;
};

template <typename T>
class PtrBase {
public:
  constexpr PtrBase() noexcept = default;

  constexpr PtrBase(const PtrBase &) = delete;

  constexpr PtrBase& operator=(const PtrBase&) = delete;

  [[nodiscard]]
  const T* Get() const noexcept {
    if (ref_counter_ != nullptr) {
      return ref_counter_->Get();
    }
    return nullptr;
  }

  constexpr auto UseCount() const noexcept {
    return ref_counter_ ? ref_counter_->UseCount() : 0;
  }

  template <typename T2>
  constexpr void Swap(PtrBase<T2> &other) noexcept {
    tystl::Swap(ref_counter_, other.ref_counter_);
  }

private:
  friend class SharedPtr<T>;
  friend class WeakPtr<T>;

  constexpr void Init(T *ptr) {
    ptr_ = ptr;
    ref_counter_ = new RefCount<T>(ptr);
  }

  constexpr void AddRef() const noexcept {
    if (ref_counter_) {
      ref_counter_->AddRef();
    }
  }

  constexpr void SubRef() const noexcept {
    if (ref_counter_) {
      ref_counter_->SubRef();
    }
  }

  constexpr void AddWRef() const noexcept {
    if (ref_counter_) {
      ref_counter_->AddWRef();
    }
  }

  constexpr void SubWRef() const noexcept {
    if (ref_counter_) {
      ref_counter_->SubWRef();
    }
  }

  template <typename T2>
  constexpr void CopyPtrFrom(const PtrBase<T2> &other) noexcept {
    ptr_ = other.ptr_;
    ref_counter_ = other.ref_counter_;
  }

  template <typename T2>
  constexpr void MoveConstructFrom(PtrBase<T2> &&other) noexcept {
    ptr_ = std::exchange(other.ptr_, nullptr);
    ref_counter_ = std::exchange(other.ptr_, nullptr);
  }

  template <typename T2>
  constexpr void CopyConstructFromShared(const SharedPtr<T2> &other) noexcept {
    other.AddRef();
    CopyPtrFrom(other);
  }

  template <typename T2>
  constexpr void WeaklyConstructFrom(const PtrBase<T2> &other) noexcept {
    CopyPtrFrom(other);
    AddWRef();
  }

  template <typename T2>
  constexpr bool ConstructFromWeak(const WeakPtr<T2> &other) noexcept {
    if (other.ref_counter_ && other.ref_counter_->TryAddRef()) {
      CopyPtrFrom(other);
      return true;
    }
    return false;
  }

private:
  T* ptr_ = nullptr;
  RefCount<T>* ref_counter_ = nullptr;
};

template <typename T>
class SharedPtr : public PtrBase<T> {
private:
  using Base = PtrBase<T>;

  template <typename>
  friend class EnableSharedFromThis;

public:
  constexpr SharedPtr() noexcept = default;

  constexpr SharedPtr(std::nullptr_t) noexcept {}

  constexpr explicit SharedPtr(T *ptr) {
    Base::Init(ptr);
    // If this class is derived from EnableSharedFromThis
    // and then assign 'this' shared ptr to weak this ptr.
    if constexpr (CanEnableShared<T>) {
      ptr->weak_this_ = *this;
    }
  }

  constexpr SharedPtr(const SharedPtr &other) noexcept {
    Base::CopyConstructFromShared(other);
  }

  constexpr SharedPtr(SharedPtr &&other) noexcept {
    Base::MoveConstructFrom(tystl::Move(other));
  }

  constexpr SharedPtr& operator=(SharedPtr other) noexcept {
    this->Swap(other);
    return *this;
  }

  template <typename T2>
  constexpr SharedPtr(const WeakPtr<T2> &other) noexcept {
    Base::ConstructFromWeak(other);
  }

  constexpr ~SharedPtr() {
    Base::SubRef();
  }

  constexpr T& operator*() noexcept {
    return *Base::ptr_;
  }

  constexpr const T& operator*() const noexcept {
    return *Base::ptr_;
  }

  constexpr T* operator->() const noexcept {
    return Base::ptr_;
  }

  constexpr explicit operator bool() const noexcept {
    return static_cast<bool>(Base::ptr_);
  }
};

template <typename T>
class WeakPtr : public PtrBase<T> {
  using Base = PtrBase<T>;
public:
  constexpr WeakPtr() noexcept = default;

  constexpr WeakPtr(std::nullptr_t) noexcept {}

  constexpr WeakPtr(const SharedPtr<T> &other) noexcept {
    Base::WeaklyConstructFrom(other);
  }

  constexpr WeakPtr(const WeakPtr &other) noexcept {
    Base::WeaklyConstructFrom(other);
  }

  constexpr WeakPtr(WeakPtr &&other) noexcept {
    Base::MoveConstructFrom(std::move(other));
  }

  constexpr WeakPtr& operator=(WeakPtr other) noexcept {
    this->Swap(other);
    return *this;
  }

  constexpr ~WeakPtr() {
    Base::SubWRef();
  }

  [[nodiscard]]
  constexpr SharedPtr<T> Lock() const noexcept {
    SharedPtr<T> result;
    result.ConstructFromWeak(*this);
    return result;
  }

  [[nodiscard]]
  constexpr bool Expired() const noexcept {
    return Base::ref_counter_->UseCount() == 0;
  }
};

template <typename T>
class EnableSharedFromThis {
protected:
  constexpr EnableSharedFromThis() noexcept : weak_this_() {}

  constexpr EnableSharedFromThis(const EnableSharedFromThis &) noexcept {}

  constexpr ~EnableSharedFromThis() = default;

  constexpr EnableSharedFromThis& operator=(const EnableSharedFromThis &) noexcept {
    return *this;
  }

public:
  constexpr SharedPtr<T> SharedFromThis() {
    return SharedPtr<T>(weak_this_);
  }

  constexpr SharedPtr<const T> SharedFromThis() const {
    return SharedPtr<const T>(weak_this_);
  }

private:
  template <typename>
  friend class SharedPtr;

  mutable WeakPtr<T> weak_this_;
};


template <typename T, typename ...Args>
  requires std::is_constructible_v<T, Args...>
constexpr SharedPtr<T> MakeShared(Args &&...args) {
  return SharedPtr<T>(new T(std::forward<Args>(args)...));
}
```