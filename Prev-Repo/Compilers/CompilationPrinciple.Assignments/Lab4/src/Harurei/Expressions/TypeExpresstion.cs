using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class TypeExpresstion(SyntaxToken typeToken) : ExpressionNode
{
    public SyntaxToken TypeToken { get; } = typeToken;

    public override SyntaxKind Kind => SyntaxKind.TypeExpresstion;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        return TypeToken.Kind switch {
            SyntaxKind.TypeInt or SyntaxKind.KeywordInt => new EvaluateResult(null, SymbolKind.Int, true),
            SyntaxKind.TypeFloat or SyntaxKind.KeywordFloat => new EvaluateResult(null, SymbolKind.Float, true),
            _ => throw new System.Exception($"Unknown type in {TypeToken.Word}")
        }; ;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return TypeToken;
    }
}
