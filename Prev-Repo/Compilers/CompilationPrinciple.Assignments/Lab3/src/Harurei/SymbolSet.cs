using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using ConsoleTables;
using Hakurei.Extension;

namespace Hakurei;

public class SymbolSet : IEnumerable<SyntaxSymbolNode>
{
    public SymbolSet() => Value = [];

    public SymbolSet(HashSet<SyntaxSymbolNode> value) => Value = value;

    public HashSet<SyntaxSymbolNode> Value { get; private set; }

    public int Count => Value.Count;

    public bool Add(SyntaxSymbolNode symbol) => Value.Add(symbol);

    public void UnionWith(SymbolSet that) => Value.UnionWith(that.Value);

    public IEnumerator<SyntaxSymbolNode> GetEnumerator() => (Value as IEnumerable<SyntaxSymbolNode>).GetEnumerator();

    IEnumerator IEnumerable.GetEnumerator() => (Value as IEnumerable).GetEnumerator();

    public SymbolSet DropEmptySymbol()
    {
        var result = Value.Where(item => !item.IsEmptySymbol()).ToHashSet();
        return new SymbolSet(result);
    }

    public bool HasIntersection(SymbolSet that) => Value.HasIntersection(that.Value);

    public static void PrettyPrint(string setName, Dictionary<SyntaxSymbolNode, SymbolSet> symbolSets)
    {
        string[] heading = ["Symbol", setName];
        var table = new ConsoleTable(heading);
        foreach (var (symbol, symbolSet) in symbolSets)
        {
            string[] row = [symbol.ToString(), $"{{{string.Join(',', symbolSet)}}}"];
            table.AddRow(row);
        }
        table.Write();
        Console.WriteLine();
    }
}
