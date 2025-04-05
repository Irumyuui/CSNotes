using System;
using System.Diagnostics;

#if DEBUG
using Dumpify;
#endif

using static System.Math;

void Main(Scanner cin, TextWriter cout)
{

}

#if DEBUG

/*
"""

""",
"""

""",
"""

""",
"""

""",
*/

var questions = new List<string>()
{
"""

""",
"""

""",
"""

""",
"""

""",
"""

""",
"""

""",
};

foreach (var (id, question) in questions.WithIndex())
{
    using var reader = new StringReader(question);
    using var writer = new StringWriter();

    var scanner = new Scanner(reader);

    Console.WriteLine($"Test {id + 1}: ");

    try
    {
        Main(scanner, writer);
    }
    catch (Exception e)
    {
        Console.WriteLine(e);
        break;
    }

    var result = writer.ToString();
    Console.WriteLine(result);
    Console.Out.Flush();
}

#else
Console.SetOut(new StreamWriter(Console.OpenStandardOutput())
{
    AutoFlush = false,
});
Main(new Scanner(Console.In), Console.Out);
Console.Out.Flush();
#endif

#region TemplateCode

public class Scanner
{
    private TextReader _reader;
    private List<string> _buffer = new();

    public Scanner(TextReader reader) => _reader = reader;

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    private void ReadNextLine()
    {
        while (_buffer.Count is 0)
        {
            var line = _reader.ReadLine() ?? throw new InvalidOperationException("Empty read line.");
            _buffer.AddRange(line.Split().Reverse());
        }
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public string NextWord()
    {
        ReadNextLine();
        var text = _buffer.Last();
        _buffer.RemoveAt(^1);
        return text;
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public T Next<T>(IFormatProvider? p = null) where T : IParsable<T>
    {
        return T.Parse(NextWord(), p);
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2) Next<T1, T2>(IFormatProvider? p1 = null, IFormatProvider? p2 = null) where T1 : IParsable<T1> where T2 : IParsable<T2>
    {
        var t1 = Next<T1>(p1);
        return (t1, Next<T2>(p2));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3) Next<T1, T2, T3>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3>
    {
        var (t1, t2) = Next<T1, T2>(p1, p2);
        return (t1, t2, Next<T3>(p3));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4) Next<T1, T2, T3, T4>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4>
    {
        var (t1, t2, t3) = Next<T1, T2, T3>(p1, p2, p3);
        return (t1, t2, t3, Next<T4>(p4));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4, T5) Next<T1, T2, T3, T4, T5>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null, IFormatProvider? p5 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4> where T5 : IParsable<T5>
    {
        var (t1, t2, t3, t4) = Next<T1, T2, T3, T4>(p1, p2, p3, p4);
        return (t1, t2, t3, t4, Next<T5>(p5));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4, T5, T6) Next<T1, T2, T3, T4, T5, T6>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null, IFormatProvider? p5 = null, IFormatProvider? p6 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4> where T5 : IParsable<T5> where T6 : IParsable<T6>
    {
        var (t1, t2, t3, t4, t5) = Next<T1, T2, T3, T4, T5>(p1, p2, p3, p4, p5);
        return (t1, t2, t3, t4, t5, Next<T6>(p6));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4, T5, T6, T7) Next<T1, T2, T3, T4, T5, T6, T7>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null, IFormatProvider? p5 = null, IFormatProvider? p6 = null, IFormatProvider? p7 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4> where T5 : IParsable<T5> where T6 : IParsable<T6> where T7 : IParsable<T7>
    {
        var (t1, t2, t3, t4, t5, t6) = Next<T1, T2, T3, T4, T5, T6>(p1, p2, p3, p4, p5, p6);
        return (t1, t2, t3, t4, t5, t6, Next<T7>(p7));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4, T5, T6, T7, T8) Next<T1, T2, T3, T4, T5, T6, T7, T8>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null, IFormatProvider? p5 = null, IFormatProvider? p6 = null, IFormatProvider? p7 = null, IFormatProvider? p8 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4> where T5 : IParsable<T5> where T6 : IParsable<T6> where T7 : IParsable<T7> where T8 : IParsable<T8>
    {
        var (t1, t2, t3, t4, t5, t6, t7) = Next<T1, T2, T3, T4, T5, T6, T7>(p1, p2, p3, p4, p5, p6, p7);
        return (t1, t2, t3, t4, t5, t6, t7, Next<T8>(p8));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public (T1, T2, T3, T4, T5, T6, T7, T8, T9) Next<T1, T2, T3, T4, T5, T6, T7, T8, T9>(IFormatProvider? p1 = null, IFormatProvider? p2 = null, IFormatProvider? p3 = null, IFormatProvider? p4 = null, IFormatProvider? p5 = null, IFormatProvider? p6 = null, IFormatProvider? p7 = null, IFormatProvider? p8 = null, IFormatProvider? p9 = null) where T1 : IParsable<T1> where T2 : IParsable<T2> where T3 : IParsable<T3> where T4 : IParsable<T4> where T5 : IParsable<T5> where T6 : IParsable<T6> where T7 : IParsable<T7> where T8 : IParsable<T8> where T9 : IParsable<T9>
    {
        var (t1, t2, t3, t4, t5, t6, t7, t8) = Next<T1, T2, T3, T4, T5, T6, T7, T8>(p1, p2, p3, p4, p5, p6, p7, p8);
        return (t1, t2, t3, t4, t5, t6, t7, t8, Next<T9>(p9));
    }

    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
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

    public static IEnumerable<(int Index, T Value)> WithIndex<T>(this List<T> self)
    {
        for (int i = 0; i < self.Count; i++)
        {
            yield return (i, self[i]);
        }
    }
}

public static class ArrayExtensions
{
    public static void Sort<T>(this T[] self)
        => Array.Sort(self);

    public static void Sort<T>(this T[] self, Comparison<T> comparable)
        => Array.Sort(self, comparable);
}

#if DEBUG
#else
public static class DebugExtensions
{
    [System.Runtime.CompilerServices.MethodImpl(System.Runtime.CompilerServices.MethodImplOptions.AggressiveInlining)]
    public static void Dump<T>(this T self) { }
}
#endif

#endregion