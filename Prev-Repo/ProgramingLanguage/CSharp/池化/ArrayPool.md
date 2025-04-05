# ArrayPool

`System.Buffers.ArrayPool<T>` 是一个数组版本的池化方案。

如果需要多次分配和释放数组，使用池化来进行分配是一个更好的选择，可以减轻 GC 的压力。

```csharp
var arr = System.Buffers.ArrayPool<int>.Shared.Rent(10);
for (int i = 0; i < arr.Length; i++)
{
    arr[i] = i;
}
Console.WriteLine(string.Join(", ", arr));
System.Buffers.ArrayPool<int>.Shared.Return(arr);
```
