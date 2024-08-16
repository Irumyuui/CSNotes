# Disjoint Set

```csharp
public class DisjointSet
{
    private readonly int[] _data;

    public int Length => _data.Length;

    public int SetCount { get; private set; }

    public DisjointSet(int length)
    {
        _data = new int[length];
        for (int i = 0; i < length; i++)
            _data[i] = -1;
        SetCount = length;
    }

    public int Find(int x) => _data[x] < 0 ? x : _data[x] = Find(_data[x]);

    public int this[int x]
    {
        get => Find(x);
        set => Union(x, value);
    }

    public bool IsSameSet(int x, int y) => Find(x) == Find(y);

    public bool Union(int x, int y)
    {
        x = Find(x);
        y = Find(y);
        if (x == y) return false;
        if (_data[x] > _data[y])
        {
            (x, y) = (y, x);
        }
        _data[x] += _data[y];
        _data[y] = x;
        SetCount--;
        return true;
    }

    public int GetSetSize(int x) => _data[Find(x)];
}
```