using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer;

public enum SymbolKind
{
    Int,
    Float,
    Double,
    Void,
    Unknown
}

public class EnvironmentSymbolTableItem(SymbolKind kind, object? value)
{
    public SymbolKind Kind { get; set; } = kind;

    public object? Value { get; set; } = value;

    // public long Address { get; set; }

    public override string ToString() => $"{{Type: {Kind}; Value: {(Value is null ? "null" : Value)}}}";
}

public class EnvironmentSymbolTable(in EnvironmentSymbolTable? prevTable = null)
{

    // public List<string> Diagostics { get; private set; } = [];

    public Dictionary<string, EnvironmentSymbolTableItem> Table { get; private set; } = [];

    /// <summary>
    /// 作为前一个作用域的符号表，当要实现函数以及作用域嵌套时
    /// </summary>
    /// <value></value>
    public EnvironmentSymbolTable? PrevTable { get; private set; } = prevTable;

    public bool TryGet(string identifierName, out EnvironmentSymbolTableItem? result) => Table.TryGetValue(identifierName, out result);

    public bool ContainsKey(string identifierName) => Table.ContainsKey(identifierName);

    public void Add(string identifierName, EnvironmentSymbolTableItem item) => Table.Add(identifierName, item);

    public bool TryAdd(string identifierName, EnvironmentSymbolTableItem item) => Table.TryAdd(identifierName, item);

    public EnvironmentSymbolTableItem this[string identifierName]
    {
        get => Table[identifierName];
        set => Table[identifierName] = value;
    }

    public void PrettyPrint()
    {
        var consoleTable = new ConsoleTables.ConsoleTable(
                "IdentifierName", "Type", "Value"
            );

        foreach (var (key, value) in Table) {
            consoleTable.AddRow(
                key.ToString(), value.Kind, value.Value is null ? "null" : value.Value.ToString()
            );
        }

        consoleTable.Write();
        System.Console.WriteLine();
    }
}
