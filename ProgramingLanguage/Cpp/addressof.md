# addressof 实现

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