# std::same_as 实现

先实现一个谓词，然后再通过这个谓词来约束 SameAs ，这样 `SameAs<A, B>` 和 `SameAs<B, A>` 会被认为是同一个谓词。

```cpp
template <typename A, typename B>
constexpr bool IsSame = false;

template <typename T>
constexpr bool IsSame<T, T> = true;

template <typename A, typename B>
concept SameHelper = IsSame<A, B>;

template <typename A, typename B>
concept SameAs = SameHelper<A, B> && SameHelper<B, A>;
```
