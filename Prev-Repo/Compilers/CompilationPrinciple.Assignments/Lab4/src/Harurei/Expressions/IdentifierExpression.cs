using System.Collections.Generic;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class IdentifierExpression(SyntaxToken identifierToken) : ExpressionNode
{
    public SyntaxToken IdentifierToken { get; } = identifierToken;

    public override SyntaxKind Kind => SyntaxKind.IdentifierExpression;

    public override EvaluateResult Execute(EnvironmentSymbolTable environmentSymbolTable, params object[] args)
    {
        if (args.Length is 1 && args[0] is EvaluateResult type && type.Kind is SymbolKind.Int or SymbolKind.Float && type.DefindVariables is true) {
            if (!environmentSymbolTable.TryAdd(IdentifierToken.Word, new EnvironmentSymbolTableItem(type.Kind, null))) {
                throw new System.Exception($"Redefine variable {IdentifierToken.Word} : {type.Kind}");
            }
            return type;
        } else {
            if (environmentSymbolTable.TryGet(IdentifierToken.Word, out var result)) {
                if (result?.Value is null) {
                    throw new System.Exception($"Variable {IdentifierToken.Word} uninitialized.");
                }
                return new EvaluateResult(result.Value, result.Kind);
            }
            throw new System.Exception($"Undefine variable {IdentifierToken.Word}");
        }
    }

    public override IEnumerable<IExpressionNode> GetChildren()
    {
        yield return IdentifierToken;
    }
}
