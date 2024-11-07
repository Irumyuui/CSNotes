# addressof 实现

- 为什么需要先转换为 `const volatile` ：模板 `T` 可能带 `volatile` ，换句话来说就是为一些接口擦屁股用的

```c++
template <typename T>
[[nodiscard]]
constexpr auto addressof(T& val) noexcept -> T* {
    if constexpr (std::is_object_v<std::remove_reference_t<T>>) {
        return reinterpret_cast<T*>(
            &const_cast<char&>(reinterpret_cast<const volatile char&>(val)));
    } else {
        return &val;
    }
}
```
