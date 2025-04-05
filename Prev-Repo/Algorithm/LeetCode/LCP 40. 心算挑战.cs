using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

public class Solution
{
    public int MaxmiumScore(int[] cards, int cnt)
    {
        Array.Sort(cards, (left, right) => right.CompareTo(left));

        int ans = 0;
        for (int i = 0; i < cnt; i++)
        {
            ans += cards[i];
        }
        if (ans % 2 == 0)
        {
            return ans;
        }

        using var eve = new NativeMemoryList<int>((nuint)cards.Length);
        using var odd = new NativeMemoryList<int>((nuint)cards.Length);
        for (int i = cnt; i < cards.Length; i++)
        {
            (cards[i] % 2 == 0 ? eve : odd).Add(cards[i]);
        }

        uint vis = 0;
        int ret = 0;
        for (int i = cnt - 1; i >= 0; i--)
        {
            if (vis == 3) break;

            if (cards[i] % 2 != 0)
            {
                if (eve.Count > 0)
                {
                    vis |= 1;
                    ret = Math.Max(ret, ans - cards[i] + eve.First);
                }
            }
            else
            {
                if (odd.Count > 0)
                {
                    vis |= 2;
                    ret = Math.Max(ret, ans - cards[i] + odd.First);
                }
            }
        }

        return ret;
    }
}

[CollectionBuilder(typeof(NativeMemoryList), "Create")]
public sealed class NativeMemoryList<T> : IDisposable where T : unmanaged
{
    private unsafe T* _data;
    private unsafe T* _end;
    public nuint Capacity { get; private set; }

    public nuint Count
    {
        get
        {
            unsafe
            {
                if (_data == default)
                    return 0;
                return (nuint)(_end - _data);
            }
        }
    }

    public NativeMemoryList(nuint capacity)
    {
        unsafe
        {
            TryNewCapacity(capacity);
        }
    }

    public NativeMemoryList(Span<T> span) : this((uint)span.Length)
    {
        unsafe
        {
            fixed (T* ptr = span)
            {
                ConstructFromPointer(ptr, (nuint)span.Length);
            }
        }
    }

    public NativeMemoryList(ReadOnlySpan<T> span) : this((uint)span.Length)
    {
        unsafe
        {
            fixed (T* ptr = span)
            {
                ConstructFromPointer(ptr, (nuint)span.Length);
            }
        }
    }

    private unsafe void ConstructFromPointer(T* ptr, nuint lenght)
    {
        Buffer.MemoryCopy(ptr, _data, sizeof(T) * (long)lenght, sizeof(T) * (long)lenght);
        _end = _data + lenght;
    }

    public static implicit operator NativeMemoryList<T>(Span<T> span) => new(span);

    public static implicit operator NativeMemoryList<T>(ReadOnlySpan<T> span) => new(span);

    ~NativeMemoryList()
    {
        Dispose();
        GC.SuppressFinalize(this);
    }

    public void Dispose()
    {
        unsafe
        {
            if (_data != default)
            {
                NativeMemory.Free(_data);
                _data = default;
                _end = default;
                Capacity = 0;
            }
        }
    }

    private unsafe void TryNewCapacity(nuint capacity)
    {
        if (capacity <= 0)
        {
            if (_data != default)
                NativeMemory.Free(_data);
            _data = default;
            _end = default;
            Capacity = capacity;
        }
        else if (capacity > Capacity)
        {
            if (_data == default)
            {
                _data = (T*)NativeMemory.Alloc(capacity, (nuint)sizeof(T));
                _end = _data;
                Capacity = capacity;
            }
            else
            {
                var newData = (T*)NativeMemory.Alloc(capacity, (nuint)sizeof(T));
                Buffer.MemoryCopy(_data, newData, sizeof(T) * (long)Count, sizeof(T) * (long)Count);

                var count = Count;
                NativeMemory.Free(_data);
                _data = newData;
                _end = _data + count;
                Capacity = capacity;
            }
        }
    }

    private void EnsureCapacity(nuint newCount)
    {
        if (newCount > Capacity)
        {
            unsafe
            {
                TryNewCapacity(Math.Max(Capacity * 2, newCount));
            }
        }
    }

    public ref T this[nuint index]
    {
        get
        {
            unsafe
            {
                if (_data == default || index >= Count)
                    throw new IndexOutOfRangeException();

                return ref Unsafe.AsRef<T>(_data + index);
            }
        }
    }

    public ref T this[int index]
    {
        get
        {
            if (index < 0)
                throw new IndexOutOfRangeException();
            return ref this[(nuint)index];
        }
    }

    public ref T First
    {
        get
        {
            if (Count == 0)
                throw new InvalidOperationException();

            unsafe
            {
                return ref Unsafe.AsRef<T>(_data);
            }
        }
    }

    public ref T Last
    {
        get
        {
            if (Count == 0)
                throw new InvalidOperationException();

            unsafe
            {
                return ref Unsafe.AsRef<T>(_data + Count - 1);
            }
        }
    }

    public void Add(T item)
    {
        EnsureCapacity(Count + 1);

        unsafe
        {
            *_end = item;
            _end++;
        }
    }

    public void RemoveAt(nuint index)
    {
        if (Count <= index)
            throw new IndexOutOfRangeException();

        for (nuint i = index; i + 1 < Count; i++)
        {
            this[i] = this[i + 1];
        }

        unsafe
        {
            _end--;
        }
    }

    public ref struct NativeMemoryListEnumerator
    {
        private unsafe ref T* _pointer;
        private nuint _count;
        private nuint _index;
        private ref T _current;

        public unsafe NativeMemoryListEnumerator(ref T* pointer, nuint count)
        {
            _pointer = ref pointer;
            _count = count;
        }

        public ref T Current
        {
            get
            {
                unsafe
                {
                    if (_pointer == default)
                        return ref Unsafe.NullRef<T>();
                    return ref _current;
                }
            }
        }

        public bool MoveNext()
        {
            unsafe
            {
                if (_index >= _count || _pointer == default)
                    return false;
                _current = ref Unsafe.AsRef<T>(_pointer + _index);
            }
            ++_index;
            return true;
        }
    }

    public NativeMemoryListEnumerator GetEnumerator()
    {
        unsafe
        {
            return new(ref _data, Count);
        }
    }
}

public static class NativeMemoryList
{
    public static NativeMemoryList<T> Create<T>(ReadOnlySpan<T> span) where T : unmanaged => span;
}