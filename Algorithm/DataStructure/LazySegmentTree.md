# Lazy Segment Tree

一个合适的封装模板。

```csharp
public interface ILazyTag<T> where T : new()
{
    bool Empty { get; }
}

public class LazySegmentTree<TValue, TLazy> where TValue : new() where TLazy : ILazyTag<TLazy>, new()
{
    private readonly int _n;
    private readonly TValue[] _data;
    private readonly TLazy[] _lazy;

    private Func<TValue, TValue, TValue> _opt;
    private Func<TLazy, TLazy, TLazy> _composition;
    private Func<TValue, TLazy, TValue> _mapping;

    public LazySegmentTree(int n, Func<TValue, TValue, TValue> opt, Func<TLazy, TLazy, TLazy> composition, Func<TValue, TLazy, TValue> mapping)
    {
        _n = n;
        _opt = opt;
        _composition = composition;
        _mapping = mapping;

        _data = new TValue[n * 4];
        for (int i = 0; i < _data.Length; i++)
        {
            _data[i] = new();
        }

        _lazy = new TLazy[n * 4];
        for (int i = 0; i < _lazy.Length; i++)
        {
            _lazy[i] = new();
        }
    }

    public int Length => _n;

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    private void ApplyLazyTag(int id)
    {
        if (_lazy[id].Empty)
            return;

        int lc = id * 2, rc = id * 2 + 1;
        _data[lc] = _mapping(_data[lc], _lazy[id]);
        _lazy[lc] = _composition(_lazy[lc], _lazy[id]);
        _data[rc] = _mapping(_data[rc], _lazy[id]);
        _lazy[rc] = _composition(_lazy[rc], _lazy[id]);
        _lazy[id] = new();
    }

    private void Set(int l, int r, int id, int pos, in TValue val)
    {
        if (l == r)
        {
            _data[id] = val;
            return;
        }

        ApplyLazyTag(id);
        var mid = l + (r - l) / 2;
        if (pos <= mid)
        {
            Set(l, mid, id * 2, pos, val);
        }
        else
        {
            Set(mid + 1, r, id * 2 + 1, pos, val);
        }

        _data[id] = _opt(_data[id * 2], _data[id * 2 + 1]);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public void Set(int idx, in TValue val) => Set(0, _n - 1, 1, idx, val);

    private void Apply(int l, int r, int id, int ml, int mr, in TLazy tag)
    {        
        if (l == ml && r == mr)
        {
            _data[id] = _mapping(_data[id], tag);
            _lazy[id] = _composition(_lazy[id], tag);
            return;
        }

        ApplyLazyTag(id);
        var mid = l + (r - l) / 2;
        if (mr <= mid)
        {
            Apply(l, mid, id * 2, ml, mr, tag);
        }
        else if (ml > mid)
        {
            Apply(mid + 1, r, id * 2 + 1, ml, mr, tag);
        }
        else
        {
            Apply(l, mid, id * 2, ml, mid, tag);
            Apply(mid + 1, r, id * 2 + 1, mid + 1, mr, tag);
        }

        _data[id] = _opt(_data[id * 2], _data[id * 2 + 1]);
    }

    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public void Apply(int l, int r, in TLazy tag) => Apply(0, _n - 1, 1, l, r - 1, tag);


    private TValue Query(int l, int r, int id, int ql, int qr)
    {
        if (l == ql && r == qr)
        {
            return _data[id];
        }

        ApplyLazyTag(id);
        var mid = l + (r - l) / 2;
        if (qr <= mid)
        {
            return Query(l, mid, id * 2, ql, qr);
        }
        else if (ql > mid)
        {
            return Query(mid + 1, r, id * 2 + 1, ql, qr);
        }
        else
        {
            return _opt(
                Query(l, mid, id * 2, ql, mid), Query(mid + 1, r, id * 2 + 1, mid + 1, qr)
            );
        }
    }


    [MethodImpl(MethodImplOptions.AggressiveInlining)]
    public TValue Query(int l, int r) => Query(0, _n - 1, 1, l, r - 1);
}
```

一个实现。

```csharp
Console.SetOut(new StreamWriter(Console.OpenStandardOutput())
{
    AutoFlush = false,
});

int n, q;
{
    var line = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
    (n, q) = (line[0], line[1]);
}

var seg = new LazySegmentTree<Info, LazyTag>(n, (a, b) => a + b, (a, b) => new LazyTag
{
    Value = a.Value + b.Value,
}, (a, b) => new Info
{
    L = a.L,
    R = a.R,
    Value = a.Value + b.Value * (a.R - a.L),
});

var lines = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
for (int i = 0; i < seg.Length; i++)
{
    seg.Set(i, new Info
    {
        L = i,
        R = i + 1,
        Value = lines[i]
    });
}

for (int t = 0; t < q; t++)
{
    lines = Console.ReadLine()!.Split().Select(int.Parse).ToArray();
    int opt = lines[0], l = lines[1], r = lines[2];
    l--;
    if (opt == 1)
    {
        int x = lines[3];
        seg.Apply(l, r, new LazyTag(x));
    }
    else
    {
        var result = seg.Query(l, r);
        Console.WriteLine(result.Value);
    }
}

Console.Out.Flush();
```