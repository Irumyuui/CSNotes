# Spares Table

```csharp
public class SparesTable<T>
{
    private readonly T[,] _data;
    private readonly Func<T, T, T> _combiner;
    public int Length { get; }
    public int Depth { get; }

    protected SparesTable(int length, Func<T, T, T> combiner)
    {
        Length = length;
        Depth = (int)Math.Log2(length) + 1;
        _data = new T[Depth, length];

        _combiner = combiner;
    }

    public SparesTable(ReadOnlySpan<T> data, Func<T, T, T> combiner) : this(data.Length, combiner)
    {
        for (int i = 0; i < data.Length; i++)
        {
            _data[0, i] = data[i];
        }
        for (int j = 1; j < Depth; j++)
        {
            for (int i = 0; i + (1 << j) - 1 < Length; i++)
            {
                _data[j, i] = _combiner(_data[j - 1, i], _data[j - 1, i + (1 << (j - 1))]);
            }
        }
    }

    public T Query(int l, int r)
    {
        int k = (int)Math.Log2(r - l + 1);
        return _combiner(_data[k, l], _data[k, r - (1 << k) + 1]);
    }
}
```