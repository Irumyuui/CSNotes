using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class VarDeclarationExpression(ExpressionNode type, ExpressionNode idList) : ExpressionNode
{
    public ExpressionNode Type { get; } = type;

    public ExpressionNode IdList { get; } = idList;

    // public SyntaxToken SemicolonToken { get; } = semicolonToken;

    public override SyntaxKind Kind => SyntaxKind.VarDeclarationExpression;

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return Type;
        yield return IdList;
        // yield return SemicolonToken;
    }

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        var typeResult = Type.Execute(environmentSymbolTable);
        IdList.Execute(environmentSymbolTable, typeResult);
        return EvaluateResult.VoidResult;
    }
}
