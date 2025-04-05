using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class DeclationExpression(ExpressionNode varDeclaration, ExpressionNode? declation) : ExpressionNode
{
    public ExpressionNode VarDeclaration { get; private set; } = varDeclaration;

    public ExpressionNode? Declation { get; private set; } = declation;

    public override SyntaxKind Kind => SyntaxKind.DeclationExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        VarDeclaration.Execute(environmentSymbolTable);
        Declation?.Execute(environmentSymbolTable);
        return EvaluateResult.VoidResult;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return VarDeclaration;
        if (Declation is not null)
            yield return Declation;
    }
}
