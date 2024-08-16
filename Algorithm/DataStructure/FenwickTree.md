# Fenwick Tree

```c++
struct FenwickTree {
    int n;
    vector<int> bit;

    explicit FenwickTree(int n) : n(n), bit(n + 1) {}

    void Add(int p, int val) {
        for (int i = p; i <= n; i += (i & -i)) {
            bit[i] += val;
        }
    }

    int Ask(int p) {
        int res = 0;
        for (int i = p; i > 0; i -= (i & -i)) {
            res += bit[i];
        }
        return res;
    }
};
```

```csharp
public class FenwickTree<T>
    where T : System.Numerics.IAdditionOperators<T, T, T>,
              System.Numerics.ISubtractionOperators<T, T, T>,
              new()
{
    private T[] _data;

    public int Length => _data.Length;

    public FenwickTree(int length)
    {
        _data = new T[length];
        for (int i = 0; i < length; i ++)
            _data[i] = new();
    }

    public void Add(int index, in T value)
    {
        index ++;
        for (int i = index; i < Length; i += i & -i)
        {
            _data[i - 1] += value;
        }
    }

    public T Sum(int index)
    {
        index ++;
        T result = new();
        for (int i = index; i > 0; i -= i & -i)
        {
            result += _data[i - 1];
        }
        return result;
    }

    public T RangeSum(int l, int r) => Sum(r) - Sum(l - 1);
}
```