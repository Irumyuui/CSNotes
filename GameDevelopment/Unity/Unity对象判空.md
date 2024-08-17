# Unity 对象判空

Unity 判空有三种写法。

```csharp
// UnityEngine.Object 有重载 operator == 和 !=
if (go == null) {
    // do something
}

// 就算单独写 c# 也没这么写过
if (System.Object.ReferenceEquals(go, null)) {
    // do something
}

// 最简单的写法
if (go is null) {
    // do something
}
```

第一种方法不止会判断对象是否为空，而且会判断 `UnityEngine.Object` 的生命周期是否结束了，所以其实是最安全的。

第二种太复杂了，狗都不写。

第三种简单，也就只能判断对象是不是空的。
