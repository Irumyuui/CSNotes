using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class StatementsExpresstion(ExpressionNode statement, ExpressionNode? statements) : ExpressionNode
{
    public ExpressionNode Statement { get; } = statement;

    // public SyntaxToken SemicolonToken { get; } = semicolonToken;

    public ExpressionNode? Statements { get; } = statements;

    public override SyntaxKind Kind => SyntaxKind.StatementsExpresstion;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        Statement.Execute(environmentSymbolTable);
        Statements?.Execute(environmentSymbolTable);
        return EvaluateResult.VoidResult;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return Statement;
        // yield return SemicolonToken;
        if (Statements is not null)
            yield return Statements;
    }
}
