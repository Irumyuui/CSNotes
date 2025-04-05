using System;
using System.Collections.Generic;
using System.Runtime.CompilerServices;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class NumberExpression(SyntaxToken numberToken) : ExpressionNode
{
    public SyntaxToken NumberToken { get; } = numberToken;

    public override SyntaxKind Kind => SyntaxKind.NumberExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        if (NumberToken.Kind.IsConstantNumber()) {
            return new EvaluateResult(
                    NumberToken.Value,
                    NumberToken.Kind switch {
                        SyntaxKind.ConstantInterger => SymbolKind.Int,
                        SyntaxKind.ConstantFloat => SymbolKind.Float,
                        _ => SymbolKind.Unknown
                    });
        }
        throw new System.Exception($"Unknown number token {NumberToken}");
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return NumberToken;
    }
}
