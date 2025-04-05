using Crt.CLex;

namespace Crt.CSyntac;

public static partial class TokenExtension
{
    /// <summary>
    /// token 是申明列表的一部分
    /// </summary>
    /// <param name="token"></param>
    /// <returns></returns>
    public static bool IsPartOfDeclarationList(this Token token)
        => token.TokenType switch
        {
            ETokenType.Int => true,
            ETokenType.Double => true,
            ETokenType.Identifier => true,
            _ => false,
        };

    // public static bool IsVarDeclaration(this Token token)
    //     => token.TokenType switch
    //     {
    //         ETokenType.Int => true,
    //         ETokenType.Double => true,
    //         _ => false,
    //     };

    public static bool IsTypeSpecifier(this Token token)
        => token.TokenType switch
        {
            ETokenType.Int => true,
            ETokenType.Double => true,
            _ => false,
        };

    public static bool IsIdentifier(this Token token) => token.TokenType is ETokenType.Identifier;

    public static bool IsComma(this Token token) => token.TokenType is ETokenType.Comma;

    public static bool IsSemicolon(this Token token) => token.TokenType is ETokenType.Semicolon;

    public static bool IsBasicAssignment(this Token token) => token.TokenType is ETokenType.BasicAssignment;
}
