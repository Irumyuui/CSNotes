using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class StatementExpresstion(ExpressionNode assignStatement) : ExpressionNode
{
    public ExpressionNode AssignStatement { get; } = assignStatement;

    public override SyntaxKind Kind => SyntaxKind.StatementExpresstion;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        var result = AssignStatement.Execute(environmentSymbolTable);
        return result;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return AssignStatement;
    }
}
