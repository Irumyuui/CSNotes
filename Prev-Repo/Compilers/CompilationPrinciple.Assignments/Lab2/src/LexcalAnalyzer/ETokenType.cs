using System.ComponentModel;
using System.Security;

namespace Crt.CLex;

/// <summary>
/// token类别
/// </summary>
public enum ETokenType
{
    // 关键字

    /// <summary>
    /// void
    /// </summary>
    [Description("void")]
    Void,

    /// <summary>
    /// bool
    /// </summary>
    [Description("bool")]
    Bool,

    /// <summary>
    /// char
    /// </summary>
    [Description("char")]
    Char,
    /// <summary>
    /// short
    /// </summary>
    [Description("short")]
    Short,
    /// <summary>
    /// int
    /// </summary>
    [Description("int")]
    Int,
    /// <summary>
    /// float
    /// </summary>
    [Description("float")]
    Float,
    /// <summary>
    /// double
    /// </summary>
    [Description("double")]
    Double,

    /// <summary>
    /// if
    /// </summary>
    [Description("if")]
    If,

    /// <summary>
    /// else
    /// </summary>
    [Description("else")]
    Else,

    /// <summary>
    /// while
    /// </summary>
    [Description("while")]
    While,

    /// <summary>
    /// do
    /// </summary>
    [Description("do")]
    Do,

    /// <summary>
    /// struct
    /// </summary>
    [Description("struct")]
    Struct,

    /// <summary>
    /// return
    /// </summary>
    [Description("return")]
    Return,

    /// <summary>
    /// const
    /// </summary>
    [Description("const")]
    Const,

    // 运算符

    /// <summary>
    /// +
    /// </summary>
    [Description("+")]
    Addition,

    /// <summary>
    /// +=
    /// </summary>
    [Description("+=")]
    AdditionAssignment,

    /// <summary>
    /// ++
    /// </summary>
    [Description("++")]
    Increment,

    /// <summary>
    /// -
    /// </summary>
    [Description("-")]
    Subtraction,

    /// <summary>
    /// --
    /// </summary>
    [Description("--")]
    Decrement,

    /// <summary>
    /// -=
    /// </summary>
    [Description("-=")]
    SubtractionAssignment,

    /// <summary>
    /// *
    /// </summary>
    [Description("*")]
    Multiplication,

    /// <summary>
    /// *=
    /// </summary>
    [Description("*=")]
    MultiplicationAssignment,

    /// <summary>
    /// /
    /// </summary>
    [Description("/")]
    Division,

    /// <summary>
    /// /=
    /// </summary>
    [Description("/=")]
    DivisionAssignment,

    /// <summary>
    /// %
    /// </summary>
    [Description("%")]
    Modulo,

    /// <summary>
    /// %=
    /// </summary>
    [Description("%=")]
    ModuloAssignment,

    /// <summary>
    /// =
    /// </summary>
    [Description("=")]
    BasicAssignment,

    /// <summary>
    /// &
    /// </summary>
    [Description("&")]
    BitAnd,

    /// <summary>
    /// &=
    /// </summary>
    [Description("&=")]
    BitAndAssignmnet,

    /// <summary>
    /// |
    /// </summary>
    [Description("|")]
    BitOr,

    /// <summary>
    /// |=
    /// </summary>
    [Description("|=")]
    BitOrAssignmnet,

    /// <summary>
    /// ^
    /// </summary>
    [Description("^")]
    BitXor,

    /// <summary>
    /// ^=
    /// </summary>
    [Description("^=")]
    BitXorAssignmnet,

    /// <summary>
    /// <<
    /// </summary>
    [Description("<<")]
    BitLeftShift,

    /// <summary>
    /// <<=
    /// </summary>
    [Description("<<=")]
    BitLeftShiftAssignmnet,

    /// <summary>
    /// >>
    /// </summary>
    [Description(">>")]
    BitRightShift,

    /// <summary>
    /// >>=
    /// </summary>
    [Description(">>=")]
    BitRightShiftAssignmnet,

    /// <summary>
    /// ==
    /// </summary>
    [Description("==")]
    EqualTo,

    /// <summary>
    /// !=
    /// </summary>
    [Description("!=")]
    NotEqualTo,

    /// <summary>
    /// <
    /// </summary>
    [Description("<")]
    LessThan,

    /// <summary>
    /// >
    /// </summary>
    [Description(">")]
    GreaterThan,

    /// <summary>
    /// <=
    /// </summary>
    [Description("<=")]
    LessThanOrEqualTo,

    /// <summary>
    /// =>
    /// </summary>
    [Description("=>")]
    GreaterThanOrEqualTo,

    /// <summary>
    /// !
    /// </summary>
    [Description("!")]
    LogicalNot,

    /// <summary>
    /// &&
    /// </summary>
    [Description("&&")]
    LogicalAnd,

    /// <summary>
    /// ||
    /// </summary>
    [Description("||")]
    LogicalOr,


    // 分割符

    /// <summary>
    /// ,
    /// </summary>
    [Description(",")]
    Comma,
    /// <summary>
    /// ;
    /// </summary>
    [Description(";")]
    Semicolon,

    /// <summary>
    /// (
    /// </summary>
    [Description("(")]
    OpenParentheses,

    /// <summary>
    /// )
    /// </summary>
    [Description(")")]
    CloseParentheses,

    /// <summary>
    /// {
    /// </summary>
    [Description("{")]
    OpenBracket,

    /// <summary>
    /// }
    /// </summary>
    [Description("}")]
    CloseBracket,


    // 标志

    /// <summary>
    /// id
    /// </summary>
    [Description("identifier")]
    Identifier,

    /// <summary>
    /// num
    /// </summary>
    [Description("constant")]
    Constant,

    /// <summary>
    /// Empty
    /// </summary>
    [Description("Empty")]
    EmptyString,

    /// <summary>
    /// End
    /// </summary>
    [Description("Period")]
    Period,

    /// <summary>
    /// 错误
    /// </summary>
    [Description("Error")]
    Error,
}

public static partial class ETokenExtensions
{
    /// <summary>
    /// 获取描述
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public static string ToDescriptionString(this ETokenType value)
    {
        var attributes = value.GetType()
                             ?.GetField(value.ToString())
                             ?.GetCustomAttributes(typeof(DescriptionAttribute), false);
        return attributes?.Length is > 0 ? ((DescriptionAttribute[])(attributes))[0].Description : string.Empty;
    }
}
