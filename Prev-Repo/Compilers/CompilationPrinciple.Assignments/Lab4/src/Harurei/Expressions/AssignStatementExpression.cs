using System;
using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class AssignStatementExpression(SyntaxToken identifierToken, SyntaxToken operatorEqualToToken, ExpressionNode expression) : ExpressionNode
{
    public SyntaxToken IdentifierToken { get; } = identifierToken;

    public SyntaxToken OperatorEqualToToken { get; } = operatorEqualToToken;

    public ExpressionNode Expression { get; } = expression;

    public override SyntaxKind Kind => SyntaxKind.AssignStatementExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        if (!environmentSymbolTable.TryGet(IdentifierToken.Word, out var identifierItem) || identifierItem is null) {
            throw new System.Exception($"Variable \"{IdentifierToken.Word}\" undefined.");
            //Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
            //    $"Variable \"{IdentifierToken.Word}\" undefined."
            //);
            //return EvaluateResult.VoidResult;
        }

        var result = Expression.Execute(environmentSymbolTable, args);

        if (identifierItem.Kind is SymbolKind.Int) {
            if (result.Value is int intValue) {
                identifierItem.Value = intValue;
            } else if (result.Value is float floatValue) {
                identifierItem.Value = Convert.ToInt32(floatValue);
            } else {
                throw new System.Exception($"Error in expression: {IdentifierToken.Word} = {result.Value ?? "null"}");
                //Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
                //    $"Error in expression: {IdentifierToken.Word} = {result.Value ?? "null"}"
                //);
                //return EvaluateResult.VoidResult;
            }
        } else if (identifierItem.Kind is SymbolKind.Float) {
            if (result.Value is int intValue) {
                identifierItem.Value = (float)intValue;
            } else if (result.Value is float floatValue) {
                identifierItem.Value = floatValue;
            } else {
                throw new System.Exception($"Error in expression: {IdentifierToken.Word} = {result.Value ?? "null"}");
                //Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
                //    $"Error in expression: {IdentifierToken.Word} = {result.Value ?? "null"}"
                //);
                //return EvaluateResult.VoidResult;
            }
        } else {
            throw new System.Exception($"Unknown type {IdentifierToken.Word} : {identifierItem.Kind}");
            //Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
            //    $"Unknown type {IdentifierToken.Word} : {identifierItem.Kind}"
            //);
            //return EvaluateResult.VoidResult;
        }

        return result;
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return IdentifierToken;
        yield return OperatorEqualToToken;
        yield return Expression;
    }
}
