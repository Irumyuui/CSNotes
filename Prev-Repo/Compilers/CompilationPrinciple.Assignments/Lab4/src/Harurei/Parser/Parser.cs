using System.Collections.Generic;

using Hakurei.CodeAnalyzer.Expression;

namespace Hakurei.CodeAnalyzer;

public class Parser
{
    public Parser(string[] text)
    {
        var lexer = new Lexter(text);

        SyntaxToken curToken;
        List<SyntaxToken> tokens = [];

        do {
            curToken = lexer.NextToken();

            if (curToken.Kind is not SyntaxKind.BadToken and not SyntaxKind.CommentsEnd) {
                tokens.Add(curToken);
            }

        } while (curToken.Kind is not Hakurei.CodeAnalyzer.SyntaxKind.EndOfFile);

        Tokens = [.. tokens];

        //Diagostics = [.. lexer.Diagostics];
    }

    private SyntaxToken[] Tokens { get; }

    private int Position { get; set; }

    //public List<string> Diagostics { get; private set; }

    private SyntaxToken Peek(int offset)
    {
        var index = Position + offset;
        if (index >= Tokens.Length)
            return Tokens[^1];
        return Tokens[index];
    }

    private SyntaxToken Current => Peek(0);

    private SyntaxToken NextToken()
    {
        var current = Current;
        Position++;
        return current;
    }

    private SyntaxToken Match(SyntaxKind kind)
    {
        if (Current.Kind == kind
        || (kind is SyntaxKind.ConstantNumber && Current.Kind is SyntaxKind.ConstantInterger or SyntaxKind.ConstantFloat)
        // || (kind is SyntaxKind.Type && Current.Kind is SyntaxKind.TypeInt or SyntaxKind.TypeFloat)
        ) {
            return NextToken();
        }

        if (kind is SyntaxKind.Type && Current.Kind.IsType()) {
            return NextToken();
        }

        if (kind is SyntaxKind.ConstantNumberOrIdentifier
        && (Current.Kind.IsIdentifier() || Current.Kind.IsConstantNumber())) {
            return NextToken();
        }

        Hakurei.Diagostics.DiagosticHelper.AddDiagostic($"Unexcept {kind}, found {Current.Kind}.");

        return new SyntaxToken(kind, Current.Word, Current.Value, Current.Line, Current.Position);
    }

    [System.Obsolete]
    public ExpressionTree ParseTest()
    {
        var expression = ParseExpression();
        var endOfFileToken = Match(SyntaxKind.EndOfFile);
        return new ExpressionTree(expression, endOfFileToken);
    }

    public ExpressionTree Parse()
    {
        var expression = ParseProgram();
        var endOfFileToken = Match(SyntaxKind.EndOfFile);
        return new ExpressionTree(expression, endOfFileToken);
    }

    private ExpressionNode ParseExpression()
    {
        return ParseTerm();
    }

    private ExpressionNode ParseTerm()
    {
        var left = ParseFactor();

        while (Current.Kind is SyntaxKind.OperatorAddition
                            or SyntaxKind.OperatorSubtraction
        ) {

            var operatorToken = NextToken();
            var right = ParseFactor();

            left = new BinaryExpression(left, operatorToken, right);
        }

        return left;
    }

    private ExpressionNode ParseFactor()
    {
        var left = ParsePrimaryExpression();

        while (Current.Kind is SyntaxKind.OperatorMultiplication
                            or SyntaxKind.OperatorDivision
        ) {

            var operatorToken = NextToken();
            var right = ParsePrimaryExpression();

            left = new BinaryExpression(left, operatorToken, right);
        }

        return left;
    }

    private ExpressionNode ParsePrimaryExpression()
    {
        if (Current.Kind is SyntaxKind.SeparatorOpenParenthese) {
            var left = NextToken();
            var expression = ParseExpression();
            var right = Match(SyntaxKind.SeparatorCloseParenthese);
            return new ParenthesizedExpression(expression);
        }

        var token = Match(SyntaxKind.ConstantNumberOrIdentifier);
        return token.Kind switch {
            SyntaxKind.ConstantNumber or SyntaxKind.ConstantInterger or SyntaxKind.ConstantFloat => new NumberExpression(token),
            _ => new IdentifierExpression(token),
        };
    }

    private ExpressionNode ParseProgram()
    {
        var declation = ParseDecrationList();
        var statement = ParseStatements();

        if (declation is null) {
            Hakurei.Diagostics.DiagosticHelper.AddDiagostic($"Unexcept null declation in {nameof(ParseProgram)}");
            declation = ExpressionNode.UnknowmExpression;
        }

        return new ProgramExpression(declation, statement);
    }

    private ExpressionNode? ParseDecrationList()
    {
        if (!Current.Kind.IsType())
            return null;

        var varDeclaration = ParseVarDeclaration();
        var declation = ParseDecrationList();

        // if (declation is null) {
        //     Diagostics.Add($"Unexcept null declation in {nameof(ParseDecrationList)}");
        //     declation = ExpressionNode.UnknownExpression;
        // }

        return new DeclationExpression(varDeclaration, declation);
    }

    private ExpressionNode ParseVarDeclaration()
    {
        var type = ParseType();
        var idList = ParseIdList();
        var semicolonToken = Match(SyntaxKind.SeparatorSemicolon);

        return new VarDeclarationExpression(type, idList);
    }

    private ExpressionNode ParseType()
    {
        var typeToken = Match(SyntaxKind.Type);
        return new TypeExpresstion(typeToken);
    }

    private ExpressionNode ParseIdList()
    {
        //var identifierToken = Match(SyntaxKind.Identifier);
        var identifier = ParseIdentifier();
        var identifierListTail = ParseIdentifierListTail();
        return new IdentifierListExpression(identifier, identifierListTail);
    }

    private ExpressionNode? ParseIdentifierListTail()
    {
        if (Current.Kind is not SyntaxKind.SeparatorComma)
            return null;

        var commaToken = Match(SyntaxKind.SeparatorComma);
        //var identifierToken = Match(SyntaxKind.Identifier);
        var identifier = ParseIdentifier();
        var identifierListTail = ParseIdentifierListTail();

        return new IdentifierListTailExpression(identifier, identifierListTail);
    }

    private ExpressionNode ParseIdentifier()
    {
        var identifierToken = Match(SyntaxKind.Identifier);
        return new IdentifierExpression(identifierToken);
    }

    private ExpressionNode? ParseStatements()
    {
        if (!Current.Kind.IsIdentifier())
            return null;

        var statement = ParseStatememt();
        var semicolonToken = Match(SyntaxKind.SeparatorSemicolon);
        var statements = ParseStatements();

        return new StatementsExpresstion(statement, statements);
    }

    private ExpressionNode ParseStatememt()
    {
        var assignStatement = ParseAssignStatement();
        return new StatementExpresstion(assignStatement);
    }

    private ExpressionNode ParseAssignStatement()
    {
        var identifierToken = Match(SyntaxKind.Identifier);
        var operatorEqualToToken = Match(SyntaxKind.OperatorAssignment);
        var expression = ParseExpression();
        return new AssignStatementExpression(identifierToken, operatorEqualToToken, expression);
    }
}
