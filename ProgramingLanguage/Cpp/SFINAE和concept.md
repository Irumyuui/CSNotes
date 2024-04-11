# concept

在 `c++20` 中，提案许久的 `concept` 被加入到标准中了，这也意味着不用再写恼人的 `SFINAE` 了（除非你是一个受虐狂，喜欢对着一堆报错中找到错误的位置）。

## c++20 之前

在 `c++20` 之前，如果需要对模板实参进行编译期检查，只能使用 `SFINAE` ，或者是部分使用 `c++17` 添加的 `if constexpr` 进行编译期检查。

> `SFINAE` : Substitution Failure Is Not An Error ，替换失败不是错误，也就是在对函数模板的重载决议中，如果在模板形参替换为显示指定的类型或者是推导出的类型失败时，那么这个推导将被丢弃，并不会导致最终的编译失败。

假设我们需要实现一个输出函数，这个函数使用 `std::cout` ，将任何传入的参数输出，我们先看看一个基础写法是怎么写的。

```c++
template <typename T>
auto WriteLine(const T &val) -> void {
    std::cout << val << '\n';
}
```

很简单，对吧？问题来了，我们要怎么知道 `std::cout << val << '\n'` 中是否可以将 `T` 输出？一个简单的方式是写入，然后编译，结果自然是观察编译是否会出错。然而，如果你真的这么做了，就会得到一长串的 `operator<<` 错误，这实际上是标志着所有的重载函数都无法匹配上你所输入的类型，编译器不知道匹配哪一个，所以全部报错了。

`SFINAE` 怎么写？我们现在需要请出 `std::enable_if` 和 `std::declval` 两位佬了。`std::enable_if` 是 `SFINAE` 的核心，如果满足约束条件，那么将得到一个确定的类型，否则没有类型，使得模板实例化失败。现在我们看看该怎么写。

```c++
template <typename T>
auto WriteLine(const T &val) 
  -> typename std::enable_if<std::is_same<decltype(std::cout << val), std::ostream&>::value, void>::type {
    std::cout << val << '\n';
}
```

哦天，后面一长串是什么？这里面使用了 `std::is_same` 判断两个类型是否是一样的，然后使用 `decltype` 推断 `std::cout << val` 的返回类型。由于 `std::cout << val` 输出后的返回类型为 `std::ostream&` ，如果它能够有匹配的输出，那么最终一定会成功，`std::enable_if` 将 `void` 作为 `type` ，否则这里 `std::is_same` 实例化将失败，也带着 `std::enable_if` 实例化失败，最终使得没有匹配的 `WriteLine` 。

如果你现在编译一下，会发现现在报错不会太多了，那么这解决我们需要的编译报错问题了吗？解决了，但是你需要花费巨大心智在模板上雕出一朵花，更不用说这只是一个简单的场景了，如果这个函数具有几个模板形参，每个参数都需要很多个约束类型，最终 `SFINAE` 会往可读性的地狱发展。

## concept 和 requires

在 `c++20` 及其以后，我们可以不用再写 `SFINAE` 的代码形式了，只需要考虑 `concept` 和 `requires` 。

我们使用这两个来对刚刚的丑陋东西重写一遍。

```c++
template <typename T>
  requires requires(const T val) { std::cout << val; }
auto WriteLine(const T &val) -> void {
    std::cout << val << '\n';
}
```

至少可读性好多了，上面的 `std::enable_if` 很难看出与 `std::cout << val` 的关系，可是 `concept` 呢？

```c++
template <typename T>
concept OutputAble = requires(const T val) {
    std::cout << val;
};

template <typename T>
    requires OutputAble<T>
auto WriteLine(const T &val) -> void {
    std::cout << val << '\n';
}
```

然而实际上，这样还是多余了点，我们可以更简单点。

```c++
template <OutputAble T>
auto WriteLine(const T &val) -> void {
    std::cout << val << '\n';
}
```

这样是不是直接看懂了模板需要的类型满足是什么了，对吧？但是这还能再简单。

```c++
auto WriteLine(const OutputAble auto &val) -> void {
    std::cout << val << '\n';
}
```

直接 `auto` ，那么现在就变得非常简单了，我们连类型都不关心了，只关心输入的这玩意是否满足可以被输出，这就是 `concept` 和 `requires` 带来的能力。

那么我们看看 `concept` 和 `requires` 是什么？

```c++
template <typename T>
concept OutputAble = requires(const T val) {
    std::cout << val;
};
auto main() -> int {
    std::cout << std::boolalpha << OutputAble<int> << '\n';
}
```

它输出了 `true` 。实际上，它有点像一个模板变量，当条件满足时为 `true` ，否则为 `false` ，那么条件在哪？

```c++
requires(const T val) { std::cout << val; }
```

这就是它所满足的条件，它需要一个 `const T val` 的变量，表示检查的操作一定不会修改到 `val` ，然后在 `{}` 中，它检查了 `std::cout << val` 是否是合法的，这显然比 `std::enable_if` 自然多了。`const T val` 只在编译期中存在，因此完全不用担心会影响到性能，只需要等到

实际上，我们刚刚一步一步简化的，就是 `concept` 的一些用法，我们可以使用 `concept` 先抽象出一些 `requires` 语句，然后复用它，或者直接在模板中使用 `requires` 来约束需要满足的 `concept` ，并且这个过程是可以再组合的，不用再写晦涩难懂的 `std::enable_if` 了。
