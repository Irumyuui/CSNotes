using System;
using System.Diagnostics;
using System.Net.NetworkInformation;

namespace Hakurei.CodeAnalyzer;

public enum SyntaxKind
{
    // Keywords

    /// <summary>
    /// else
    /// </summary>
    KeywordElse,
    /// <summary>
    /// ifIdentifier
    /// </summary>
    KeywordIf,
    /// <summary>
    /// int
    /// </summary>
    KeywordInt,
    /// <summary>
    /// float
    /// </summary>
    KeywordFloat,
    /// <summary>
    /// return
    /// </summary>
    KeywordReturn,
    /// <summary>
    /// void
    /// </summary>
    KeywordVoid,
    /// <summary>
    /// while
    /// </summary>
    KeywordWhile,

    // Operator

    /// <summary>
    /// +
    /// </summary>
    OperatorAddition,
    /// <summary>
    /// -
    /// </summary>
    OperatorSubtraction,
    /// <summary>
    /// *
    /// </summary>
    OperatorMultiplication,
    /// <summary>
    /// /
    /// </summary>
    OperatorDivision,
    /// <summary>
    /// =
    /// </summary>
    OperatorAssignment,

    /// <summary>
    /// ==
    /// </summary>
    OperatorEqualTo,
    /// <summary>
    /// !=
    /// </summary>
    OperatorNotEqualTo,
    /// <summary>
    /// <
    /// </summary>
    OperatorLessThan,
    /// <summary>
    /// >
    /// </summary>
    OperatorGreaterThan,
    /// <summary>
    /// <=
    /// </summary>
    OperatorLessThanOrEqualTo,
    /// <summary>
    /// >=
    /// </summary>
    OperatorGreaterThanOrEqualTo,

    /// <summary>
    /// [
    /// </summary>
    OperatorOpenSubscript,
    /// <summary>
    /// ]
    /// </summary>
    OperatorCloseSubscript,

    // Separator

    /// <summary>
    /// ,
    /// </summary>
    SeparatorComma,
    /// <summary>
    /// ;
    /// </summary>
    SeparatorSemicolon,
    /// <summary>
    /// (
    /// </summary>
    SeparatorOpenParenthese,
    /// <summary>
    /// )
    /// </summary>
    SeparatorCloseParenthese,

    /// <summary>
    /// {
    /// </summary>
    SeparatorOpenBracket,
    /// <summary>
    /// }
    /// </summary>
    SeparatorCloseBracket,

    // Other

    /// <summary>
    /// /* 
    /// </summary>
    LeftComments,
    /// <summary>
    /// */
    /// </summary>
    RightComments,

    /// <summary>
    /// Only letter
    /// </summary>
    Identifier,

    /// <summary>
    /// Constant integer
    /// </summary>
    ConstantNumber,

    /// <summary>
    /// End of file
    /// </summary>
    EndOfFile,

    /// <summary>
    /// Bad token
    /// </summary>
    BadToken,

    /// <summary>
    /// Unknoun token.
    /// </summary>
    UnknownToken,
    Unused,

    IdentifierOrKeyword,
    Separator,
    Type,

    CommentText,
    CommentsEnd,

    NumberExpression,
    BinaryExpression,
    FunctionExpression,
    ConstantInterger,
    ConstantFloat,
    ParenthesizedExpression,   
    DeclationExpression,
    StatementExpresstion,
    ProgramExpression,
    UnknownExpression,
    VarDeclarationExpression,
    TypeExpresstion,
    IdentifierListExpression,
    IdentifierListTailExpression,
    StatementsExpresstion,
    AssignStatementExpression,
    ConstantNumberOrIdentifier,
    IdentifierExpression,

    TypeInt,
    TypeFloat,
}

public static class SyntaxKindHelper
{
    public static bool TryGetKeywordKind(string text, out SyntaxKind kind)
    {
        kind = text switch {
            "int" => SyntaxKind.KeywordInt,
            "float" => SyntaxKind.KeywordFloat,
            "else" => SyntaxKind.KeywordElse,
            "if" => SyntaxKind.KeywordIf,
            "void" => SyntaxKind.KeywordVoid,
            "while" => SyntaxKind.KeywordWhile,
            _ => SyntaxKind.UnknownToken,
        };
        return kind is not SyntaxKind.UnknownToken;
    }

    public static bool TryGetOperatorKind(string text, out SyntaxKind kind)
    {
        kind = text switch {
            "+" => SyntaxKind.OperatorAddition,
            "-" => SyntaxKind.OperatorSubtraction,
            "*" => SyntaxKind.OperatorMultiplication,
            "/" => SyntaxKind.OperatorDivision,
            "<" => SyntaxKind.OperatorLessThan,
            "<=" => SyntaxKind.OperatorLessThanOrEqualTo,
            "==" => SyntaxKind.OperatorEqualTo,
            ">=" => SyntaxKind.OperatorGreaterThanOrEqualTo,
            ">" => SyntaxKind.OperatorGreaterThan,
            "!=" => SyntaxKind.OperatorNotEqualTo,
            "=" => SyntaxKind.OperatorAssignment,
            _ => SyntaxKind.UnknownToken,
        };
        return kind is not SyntaxKind.UnknownToken;
    }

    public static bool TryGetSeparatorKind(string text, out SyntaxKind kind)
    {
        kind = text switch {
            "(" => SyntaxKind.SeparatorOpenParenthese,
            ")" => SyntaxKind.SeparatorCloseParenthese,
            "[" => SyntaxKind.OperatorOpenSubscript,
            "]" => SyntaxKind.OperatorCloseSubscript,
            "{" => SyntaxKind.SeparatorOpenBracket,
            "}" => SyntaxKind.SeparatorCloseBracket,
            "," => SyntaxKind.SeparatorComma,
            ";" => SyntaxKind.SeparatorSemicolon,
            _ => SyntaxKind.UnknownToken,
        };
        return kind is not SyntaxKind.UnknownToken;
    }

    public static bool IsPairOfOperator(char ch) => ch is '+' or '-' or '*' or '/' or '<' or '=' or '>' or '!';

    public static bool IsPairOfSeparator(char ch) => ch is '(' or ')' or '[' or ']' or '{' or '}' or ',' or ';';

    public static bool IsDropChar(char ch) => ch is ' ' or '\r' or '\n';

    public static bool IsEndOfFile(char ch) => ch is '\0';

    public static bool IsBinaryOperator(SyntaxKind kind)
        => kind is SyntaxKind.OperatorAddition
                or SyntaxKind.OperatorSubtraction
                or SyntaxKind.OperatorMultiplication
                or SyntaxKind.OperatorDivision;

    public static bool IsBinaryOperator(string text) => text is "+" or "-" or "*" or "/";
}
