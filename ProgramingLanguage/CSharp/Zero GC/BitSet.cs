public struct BitSet256
{
    private unsafe fixed byte _data[32];

    public readonly nuint Length => 256;

    [DoesNotReturn]
    private static byte ThrowOutOfRangeException() => throw new IndexOutOfRangeException("Index must be between 0 and 255");

    public byte this[nuint index]
    {
        get
        {
            if (index is < 0 or > 255)
            {
                ThrowOutOfRangeException();
            }

            var byteIndex = index / 8;
            var bitIndex = index % 8;

            unsafe
            {

                return (byte)((_data[byteIndex] >> (byte)bitIndex) & 1);
            }
        }
        set
        {
            if (index is < 0 or > 255)
            {
                ThrowOutOfRangeException();
            }

            var byteIndex = index / 8;
            var bitIndex = index % 8;

            unsafe
            {

                _data[byteIndex] = (byte)((_data[byteIndex] & ~(1 << (byte)bitIndex)) | ((value & 1) << (byte)bitIndex));
            }
        }
    }

    public static BitSet256 operator &(BitSet256 left, BitSet256 right)
    {
        BitSet256 result = default;
        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                result._data[i] = (byte)(left._data[i] & right._data[i]);
            }
        }
        return result;
    }

    public static BitSet256 operator |(BitSet256 left, BitSet256 right)
    {

        BitSet256 result = default;
        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                result._data[i] = (byte)(left._data[i] | right._data[i]);
            }
        }
        return result;
    }

    public static BitSet256 operator ^(BitSet256 left, BitSet256 right)
    {
        BitSet256 result = default;
        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                result._data[i] = (byte)(left._data[i] ^ right._data[i]);
            }
        }
        return result;
    }


    public static BitSet256 operator ~(BitSet256 value)
    {
        BitSet256 result = default;
        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                result._data[i] = (byte)(~value._data[i]);
            }
        }
        return result;
    }

    public byte[] ToByteArray()
    {
        var bytes = new byte[32];
        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                bytes[i] = _data[i];
            }
        }
        return bytes;
    }

    public void ToByteArray(ref byte[] bytes)
    {
        if (!TryToByteArray(ref bytes))
        {
            throw new ArgumentException("Array must be at least 32 bytes long");
        }
    }

    public bool TryToByteArray(ref byte[] bytes)
    {
        if (bytes.Length < 32)
        {
            return false;
        }

        unsafe
        {
            for (int i = 0; i < 32; i++)
            {
                bytes[i] = _data[i];
            }
        }

        return true;
    }
}