# 值类型 Enumerator

如果需要对自定义集合类型做优化的话，那么一个值得考虑的点是 `foreach` 中关于 `Enumerator` 的使用。

如果这个地方的对象是个引用类型的话，那么对 GC 存在一定压力。

如果是值类型的话，就这么写就好了。

```csharp
public class Array<T>(int length)
{
    private readonly T[] data = new T[length];

    public T this[int index] {
        get => data[index];
        set => data[index] = value;
    }

    public T this[System.Index index] {
        get => this[index.GetOffset(length)];
        set => this[index.GetOffset(length)] = value;
    }

    public int Length => length;

    // 这里直接返回这个值类型的 Enumerator
    // foreach 只看方法签名，有就直接调用了
    public Enumerator GetEnumerator() => new Enumerator(this);

    // 内部创建一个值类型 Enumerator
    public struct Enumerator(Array<T> data) : IEnumerator<T>
    {
        private int currentIndex = -1;

        public readonly T Current => data[currentIndex] ?? throw new InvalidOperationException();

        readonly object IEnumerator.Current => Current!;

        public void Dispose() => currentIndex = -1;

        public bool MoveNext() => ++currentIndex < data.Length;

        public void Reset() => currentIndex = -1;
    }
}
```