using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class ParenthesizedExpression(ExpressionNode expression) : ExpressionNode
{
    // public SyntaxToken OpenParenthesisToken { get; } = openParenthesisToken;

    public ExpressionNode Expression { get; } = expression;

    // public SyntaxToken CloseParenthesisToken { get; } = closeParenthesisToken;

    public override SyntaxKind Kind => SyntaxKind.ParenthesizedExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        return Expression.Execute(environmentSymbolTable, args);
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        // yield return OpenParenthesisToken;
        yield return Expression;
        // yield return CloseParenthesisToken;
    }
}
