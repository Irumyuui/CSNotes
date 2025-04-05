using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class ProgramExpression(ExpressionNode declation, ExpressionNode? statement) : ExpressionNode
{
    public ExpressionNode Declation { get; private set; } = declation;

    public ExpressionNode? Statement { get; private set; } = statement;

    public override SyntaxKind Kind => SyntaxKind.ProgramExpression;

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return Declation;
        if (Statement is not null)
            yield return Statement;
    }

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        Declation.Execute(environmentSymbolTable);
        Statement?.Execute(environmentSymbolTable);
        return EvaluateResult.VoidResult;
    }
}
