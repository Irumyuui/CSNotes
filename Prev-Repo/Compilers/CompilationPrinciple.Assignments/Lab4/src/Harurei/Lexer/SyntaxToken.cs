using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using Hakurei.CodeAnalyzer;

namespace Hakurei.CodeAnalyzer.Expression;

public class SyntaxToken(SyntaxKind kind, string word, in object? value, int line, int position) : IExpressionNode
{
    private readonly SyntaxKind kind = kind;

    public SyntaxKind Kind => kind;

    public string Word { get; } = word;

    public object? Value { get; } = value;

    public int Line { get; } = line;

    public int Position { get; } = position;

    public IEnumerable<IExpressionNode> GetChildren() => Enumerable.Empty<IExpressionNode>();

    public static SyntaxToken UnknownToken { get; } = new SyntaxToken(SyntaxKind.UnknownExpression, "", null, -1, -1);

    public override string ToString()
        => $"{{Kind: {Kind}; Word: {Word}; Value: {Value ?? "null"}; In: {Line}:{Position} }}";

    public bool Equals(SyntaxToken? that) => Word == that?.Word;

    public override bool Equals(object? obj) => Equals(obj as SyntaxToken);

    public override int GetHashCode() => HashCode.Combine(Word);
}
