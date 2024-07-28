using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;

[CollectionBuilder(typeof(NativeMemoryBufferBuilder), "Create")]
public sealed class NativeMemoryBuffer<T> : IDisposable where T : unmanaged
{
    private unsafe T* _pointer;

    public nuint Length { get; }

    public NativeMemoryBuffer(nuint lenght)
    {
        Length = lenght;
        unsafe
        {
            _pointer = (T*)NativeMemory.Alloc(lenght, (nuint)sizeof(T));
        }
    }

    public NativeMemoryBuffer(Span<T> span) : this((nuint)span.Length)
    {
        unsafe
        {
            fixed (T* ptr = span)
            {
                Buffer.MemoryCopy(ptr, _pointer, sizeof(T) * span.Length, sizeof(T) * span.Length);
            }
        }
    }

    public NativeMemoryBuffer(ReadOnlySpan<T> span) : this((nuint)span.Length)
    {
        unsafe
        {
            fixed (T* ptr = span)
            {
                Buffer.MemoryCopy(ptr, _pointer, sizeof(T) * span.Length, sizeof(T) * span.Length);
            }
        }
    }

    public static unsafe implicit operator T*(NativeMemoryBuffer<T> buffer) => buffer._pointer;

    public static implicit operator NativeMemoryBuffer<T>(Span<T> span) => new(span);

    public static implicit operator NativeMemoryBuffer<T>(ReadOnlySpan<T> span) => new(span);

    ~NativeMemoryBuffer()
    {
        Dispose();
        GC.SuppressFinalize(this);
    }

    public void Dispose()
    {
        unsafe
        {
            if (_pointer != default)
            {
                NativeMemory.Free(_pointer);
                _pointer = default;
            }
        }
    }

    public ref T this[nuint index]
    {
        get
        {
            unsafe
            {
                if (index >= Length || _pointer == default)
                    throw new IndexOutOfRangeException();

                return ref Unsafe.AsRef<T>(_pointer + index);
            }
        }
    }

    public ref struct NativeMemoryBufferEnumerator
    {
        private unsafe readonly ref T* _pointer;
        private nuint _length;
        private nuint _index;
        private ref T _current;

        public unsafe NativeMemoryBufferEnumerator(ref T* pointer, nuint length)
        {
            _pointer = ref pointer;
            _length = length;
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
                if (_index >= _length || _pointer == default)
                    return false;

                _current = ref Unsafe.AsRef<T>(_pointer + _index);
            }
            _index++;
            return true;
        }
    }

    public NativeMemoryBufferEnumerator GetEnumerator()
    {
        unsafe
        {
            return new(ref _pointer, Length);
        }
    }
}

public static class NativeMemoryBufferBuilder
{
    public static NativeMemoryBuffer<T> Create<T>(ReadOnlySpan<T> span) where T : unmanaged => new(span);
}