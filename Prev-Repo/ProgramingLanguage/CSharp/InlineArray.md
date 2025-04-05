# 内联数组

固定大小的，可以值类型分配的，数组。

要求只能一个字段。

```csharp
[System.Runtime.CompilerServices.InlineArray(1024)]
public struct Buffer
{
    private byte _element;
}
```

这个就是一个值类型的 `byte` 数组。