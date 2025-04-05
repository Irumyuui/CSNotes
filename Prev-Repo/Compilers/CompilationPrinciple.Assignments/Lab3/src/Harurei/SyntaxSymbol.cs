using System;

namespace Hakurei;

public interface ISymbol
{
    public string Name { get; }

}

public class SyntaxSymbolNode : ISymbol
{
    public SyntaxSymbolNode(string name) => Name = name;

    public string Name { get; }

    public override string ToString() => $"<{(string.IsNullOrEmpty(Name) ? "Empty" : Name)}>";

    public bool Equals(ISymbol? symbol) => symbol is not null && Name == symbol.Name;

    public bool IsEmptySymbol() => Name == string.Empty;

    public bool IsEnd() => Name == End.Name;

    public override bool Equals(object? obj) => Equals(obj as ISymbol);

    public override int GetHashCode() => HashCode.Combine(Name);


    public static bool operator ==(SyntaxSymbolNode left, SyntaxSymbolNode right) => left.Equals(right);


    public static bool operator !=(SyntaxSymbolNode left, SyntaxSymbolNode right) => !left.Equals(right);


    public static bool operator ==(ISymbol left, SyntaxSymbolNode right) => left.Equals(right);


    public static bool operator !=(ISymbol left, SyntaxSymbolNode right) => !left.Equals(right);


    public static bool operator ==(SyntaxSymbolNode left, ISymbol right) => left.Equals(right);


    public static bool operator !=(SyntaxSymbolNode left, ISymbol right) => !left.Equals(right);

    private static readonly SyntaxSymbolNode _empty = new SyntaxSymbolNode(string.Empty);

    private static readonly SyntaxSymbolNode _end = new SyntaxSymbolNode("$");

    public static SyntaxSymbolNode Empty => _empty;

    public static SyntaxSymbolNode End => _end;
}
