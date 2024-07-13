public class Scanner
{
    private TextReader _reader;
    private List<string> _buffer = new();

    public Scanner(TextReader reader) => _reader = reader;

    private void ReadNextLine()
    {
        while (_buffer.Count is 0)
        {
            var line = _reader.ReadLine() ?? throw new InvalidOperationException("Empty read line.");
            _buffer.AddRange(line.Split().Reverse());
        }
    }

    public string NextWord()
    {
        var text = _buffer.Last();
        _buffer.RemoveAt(^1);
        return text;
    }

    public T Next<T>(IFormatProvider? p = null) where T : IParsable<T>
    {
        ReadNextLine();
        return T.Parse(NextWord(), p);
    }

    public (T1, T2) Next<T1, T2>(IFormatProvider? p1 = null, IFormatProvider? p2 = null) where T1 : IParsable<T1> where T2 : IParsable<T2>
    {
        var t1 = Next<T1>(p1);
        return (t1, Next<T2>(p2));
    }

    public (T1, T2, T3) Next<T1, T2, T3>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3>
    {
        var (t1, t2) = Next<T1, T2>(p1, p2);
        return (t1, t2, Next<T3>(p3));
    }

    public (T1, T2, T3, T4) Next<T1, T2, T3, T4>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4>
    {
        var (t1, t2, t3) = Next<T1, T2, T3>(p1, p2, p3);
        return (t1, t2, t3, Next<T4>(p4));
    }

    public T[] Next<T>(int length, IFormatProvider? p = null) where T : IParsable<T>
    {
        var arr = new T[length];
        for (int i = 0; i < length; i++)
            arr[i] = Next<T>(p);
        return arr;
    }
}

public static class ListExtensions
{
    public static void RemoveAt<T>(this List<T> self, Index index)
        => self.RemoveAt(index.GetOffset(self.Count));
}

public static class ArrayExtensions
{
    public static void Sort<T>(this T[] self)
        => Array.Sort(self);

    public static void Sort<T>(this T[] self, Comparison<T> comparable)
        => Array.Sort(self, comparable);
}