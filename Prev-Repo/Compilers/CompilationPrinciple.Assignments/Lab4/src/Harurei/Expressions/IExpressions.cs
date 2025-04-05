using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public interface IExpressionNode
{
    SyntaxKind Kind { get; }

    public IEnumerable<IExpressionNode> GetChildren();
}

public abstract class ExpressionNode : IExpressionNode
{
    public abstract SyntaxKind Kind { get; }

    public abstract IEnumerable<IExpressionNode> GetChildren();

    public abstract EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args);

    private static UnknownExpression _unknowmExpression => new();

    public static UnknownExpression UnknowmExpression => _unknowmExpression;
}
