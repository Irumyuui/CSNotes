using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class UnknownExpression : ExpressionNode
{
    public override SyntaxKind Kind => SyntaxKind.UnknownExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        //Hakurei.Diagostics.DiagosticHelper.AddDiagostic("Call unknown expression.");
        //throw new System.NotImplementedException();

        throw new System.Exception("Call unknown expression.");
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return SyntaxToken.UnknownToken;
    }
}
