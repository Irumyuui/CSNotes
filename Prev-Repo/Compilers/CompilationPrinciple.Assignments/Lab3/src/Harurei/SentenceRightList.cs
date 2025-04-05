using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;

namespace Hakurei;

public class SentenceRightList : IEnumerable<SyntaxSymbolNode>
{
    public SentenceRightList() => Right = [];

    public SentenceRightList(in List<SyntaxSymbolNode> right) => Right = right;

    public SentenceRightList(IEnumerable<SyntaxSymbolNode> right) => Right = right.ToList();

    public SentenceRightList(string text)
    {
        Right = [];
        if (string.IsNullOrEmpty(text))
        {
            Right.Add(SyntaxSymbolNode.Empty);
        }
        else
        {
            int position = 0;
            while (position < text.Length)
            {
                var current = text[position];
                if (current is '<')
                {
                    var start = position + 1;
                    var end = text.IndexOf('>', position);
                    if (end is not -1)
                    {
                        Right.Add(new SyntaxSymbolNode(text[start..end]));
                        position = end + 1;
                        continue;
                    }
                }
                Right.Add(new SyntaxSymbolNode(current.ToString()));
                position++;
            }
        }
    }

    private List<SyntaxSymbolNode> Right { get; set; }

    public int Count => Right.Count;

    public void Clear() => Right.Clear();

    public SyntaxSymbolNode this[int index]
    {
        get => Right[index];
        set => Right[index] = value;
    }

    public SyntaxSymbolNode First
    {
        get => Right[0];
        set => Right[0] = value;
    }

    public SyntaxSymbolNode Last
    {
        get => Right[^1];
        set => Right[^1] = value;
    }

    public void Add(in SyntaxSymbolNode symbol) => Right.Add(symbol);

    public void RemoveAt(Index index) => Right.RemoveAt(index.GetOffset(Right.Count));

    public void AddRange(System.Collections.Generic.IEnumerable<SyntaxSymbolNode> collection) => Right.AddRange(collection);

    public List<SyntaxSymbolNode> Slice(int start, int count)
    {
        var result = Right[start..(start + count)];
        return result;
    }

    public System.Collections.Generic.IEnumerable<SyntaxSymbolNode> GetSymbols()
    {
        foreach (var sym in Right)
            yield return sym;
    }

    public void Distinct() => Right = Right.DistinctBy(item => item.Name).ToList();

    public override string ToString() => string.Concat(Right);

    public bool Equals(SentenceRightList? that) => ToString() == that?.ToString();

    public override bool Equals(object? obj) => Equals(obj as SentenceRightList);

    public override int GetHashCode() => HashCode.Combine(ToString());

    public IEnumerator<SyntaxSymbolNode> GetEnumerator() => (Right as IEnumerable<SyntaxSymbolNode>).GetEnumerator();

    IEnumerator IEnumerable.GetEnumerator() => (Right as IEnumerable).GetEnumerator();
}
