using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class IdentifierListExpression(ExpressionNode identifier, ExpressionNode? identifierListTail) : ExpressionNode
{
    public ExpressionNode Identifier { get; } = identifier;

    public ExpressionNode? IdentifierListTail { get; } = identifierListTail;

    public override SyntaxKind Kind => SyntaxKind.IdentifierListExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        Identifier.Execute(environmentSymbolTable, args);
        IdentifierListTail?.Execute(environmentSymbolTable, args);

        return EvaluateResult.VoidResult;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return Identifier;

        if (IdentifierListTail is not null)
            yield return IdentifierListTail;
    }
}
