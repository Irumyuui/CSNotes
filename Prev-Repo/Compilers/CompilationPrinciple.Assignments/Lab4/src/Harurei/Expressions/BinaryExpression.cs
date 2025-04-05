using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class BinaryExpression(ExpressionNode left, SyntaxToken operatorToken, ExpressionNode right) : ExpressionNode
{
    public ExpressionNode Left { get; } = left;
    public SyntaxToken OperatorToken { get; } = operatorToken;
    public ExpressionNode Right { get; } = right;

    public override SyntaxKind Kind => SyntaxKind.BinaryExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        var lefrResult = Left.Execute(environmentSymbolTable);
        var rightResult = Right.Execute(environmentSymbolTable);

        return OperatorToken.Kind switch {
            SyntaxKind.OperatorAddition => lefrResult + rightResult,
            SyntaxKind.OperatorSubtraction => lefrResult - rightResult,
            SyntaxKind.OperatorMultiplication => lefrResult * rightResult,
            SyntaxKind.OperatorDivision => lefrResult / rightResult,

            _ => throw new System.Exception($"Unknown kind of operator '{OperatorToken.Word}'")
        };
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return Left;
        yield return OperatorToken;
        yield return Right;
    }
}
