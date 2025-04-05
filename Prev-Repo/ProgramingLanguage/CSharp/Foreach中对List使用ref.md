# Foreach 中对 List 使用 ref

因为 `List<T>` 没办法使用 `ref` ，在 `foreach` 中，所以要修改的话，使用 `Span<T>` 即可。但是 `List<T>` 没有提供一个方法，得到 `Span<T>` ，因此这边需要借助 `System.Runtime.InteropServices.CollectionsMarshal` 来获得。

```csharp
public static class ListExtensions
{
    public static Span<T> AsSpan<T>(this List<T> list) => System.Runtime.InteropServices.CollectionsMarshal.AsSpan(list);
}
```

然后我们就可以这么修改容器里面的内容了。

```csharp
List<int> a = [1, 2, 3];
foreach (ref var item in a.AsSpan())
{
    item = 0;
}
// a = [0, 0, 0]
```

要注意的是，因为 `List<T>` 内部的内存是会改变的，如果使用 `Add` ，之前的 `span` 是可能会失效的。
