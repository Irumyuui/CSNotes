using System;
using Hakurei.CodeAnalyzer.Expression;

namespace Hakurei.CodeAnalyzer;

[System.Obsolete("A helpful class for testing the evaluation of binary expressions.")]
public class Evaluator(ExpressionNode root)
{
    public ExpressionNode Root { get; private set; } = root;

    public EvaluateResult Evaluate() => EvaluateExpression(Root);

    private EvaluateResult EvaluateExpression(ExpressionNode node)
    {
        if (node is NumberExpression n) {
            // return (int)n.NumberToken.Value!;
            return new EvaluateResult(
                n.NumberToken.Value,
                n.NumberToken.Kind switch {
                    SyntaxKind.ConstantInterger => SymbolKind.Int,
                    SyntaxKind.ConstantFloat => SymbolKind.Float,
                    _ => throw new Exception($"Unknown type in {n.NumberToken.Kind}"),
                }
            );
        }

        if (node is BinaryExpression b) {
            var left = EvaluateExpression(b.Left);
            var right = EvaluateExpression(b.Right);

            var result = b.OperatorToken.Kind switch {
                SyntaxKind.OperatorAddition => left + right,
                SyntaxKind.OperatorSubtraction => left - right,
                SyntaxKind.OperatorMultiplication => left * right,
                SyntaxKind.OperatorDivision => left / right,
                _ => throw new Exception($"Unexpected binary operator {b.OperatorToken.Kind}")
            };

            return result;
        }

        if (node is ParenthesizedExpression p) {
            return EvaluateExpression(p.Expression);
        }

        throw new Exception($"Unexpected node {node.Kind}");
    }
}
