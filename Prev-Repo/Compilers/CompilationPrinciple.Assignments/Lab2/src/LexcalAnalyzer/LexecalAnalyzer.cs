using System.Text;
using System.Diagnostics;

namespace Crt.CLex;

/// <summary>
/// 扫描指针不再可用异常
/// </summary>
public class ScanStatusPointNotAvaliableException : Exception
{
    public ScanStatusPointNotAvaliableException() : base() { }

    public ScanStatusPointNotAvaliableException(string? message) : base(message) { }
}

/// <summary>
/// Lex字符串或字符未闭合
/// </summary>
public class CharOrStringNotCloseException : Exception
{
    public CharOrStringNotCloseException() : base()
    {

    }

    public CharOrStringNotCloseException(string? message) : base(message)
    {

    }
}

internal static class StringExtension
{
    public static bool IsEmpty(this string str) => str != string.Empty;
}

/// <summary>
/// 扫描指针状态
/// </summary>
public struct ScanStatus(int point = -1)
{
    /// <summary>
    /// 扫描指针
    /// </summary>
    /// <value></value>
    public int Point { get; private set; } = point;

    /// <summary>
    /// 指针是否可用
    /// </summary>
    public readonly bool Available => Point > -1;

    public readonly Index ToIndex()
    {
        if (!Available)
        {
            throw new ScanStatusPointNotAvaliableException();
        }
        return new Index(Point);
    }

    public override readonly string ToString() => $"{Point}";
}

public struct Token
{
    public string TokenName;
    public ETokenType TokenType;

    public Token()
    {
        TokenName = string.Empty;
        TokenType = ETokenType.Error;
    }

    public Token(in string tokenName, in ETokenType tokenType)
    {
        TokenName = tokenName;
        TokenType = tokenType;
    }

    public readonly bool Available
        => TokenType is not ETokenType.Error
        || (TokenType is ETokenType.Period && TokenName.IsEmpty())
        || !TokenName.IsEmpty();

    public readonly bool IsPeriod()
        => TokenType is ETokenType.Period;

    public override readonly string ToString() => $"{{<{TokenName}>, <{TokenType}>}}";
}

public class LexecalAnalyzer
{
    /// <summary>
    /// C代码
    /// </summary>
    /// <value></value>
    public string CodeText { get; set; }

    /// <summary>
    /// 构造一个词法分析器对象
    /// </summary>
    /// <param name="codeText">源c代码</param>
    /// <returns></returns>
    public LexecalAnalyzer(string codeText)
    {
        CodeText = ClearComments(codeText);
        Debug.WriteLine(CodeText);
        if (string.IsNullOrEmpty(CodeText))
        {
            throw new ArgumentNullException(codeText);
        }
    }

    /// <summary>
    /// 构造一个词法分析器对象
    /// </summary>
    /// <param name="codeTextArr">源c代码</param>
    /// <returns></returns>
    public LexecalAnalyzer(string[] codeTextArr) : this(ClearComments(codeTextArr))
    {

    }

    /// <summary>
    /// 清除代码注释
    /// </summary>
    /// <param name="codeText"></param>
    /// <returns></returns>
    private static string ClearComments(string codeText)
    {
        if (string.IsNullOrEmpty(codeText))
            throw new ArgumentNullException(nameof(codeText));

        var buffer = new StringBuilder();

        int first = 0;
        while (first < codeText.Length)
        {
            var left = codeText.IndexOf("/*", first);
            if (left is -1)
            {
                buffer.Append(codeText[first..]);
                break;
            }
            else
            {
                buffer.Append(codeText[first..left]);
            }
            var right = codeText.IndexOf("*/", left);
            first = right + 2;
        }

        // 处理单行注释
        var code = buffer.ToString()
                        .Split('\n')
                        .Where(line => !string.IsNullOrEmpty(line))
                        .Select(line =>
                        {
                            int p = line.IndexOf(@"//");
                            if (p is -1)
                                return line;

                            int o = 0, t = 0;
                            byte state = 0;
                            while (p < line.Length && p is not -1)
                            {
                                while (o < p)
                                {
                                    if (line[o] is '\"' && o - 1 >= 0 && line[o - 1] is not '\\')
                                    {
                                        state ^= 1;
                                    }
                                    o++;
                                }
                                while (t < p)
                                {
                                    if (line[t] is '\'' && t - 1 >= 0 && line[t - 1] is not '\\')
                                    {
                                        state ^= 2;
                                    }
                                    t++;
                                }

                                if (state is 0b00)
                                {
                                    return line[0..p];
                                }
                                else
                                {
                                    p = line.IndexOf(@"//", p + 2);
                                }
                            }

                            return line;
                        })
                        .Select(s => s.Trim())
                        .Where(s => !string.IsNullOrEmpty(s));
        buffer.Clear();
        foreach (var line in code)
        {
            buffer.Append(line);
        }

        return buffer.ToString();
    }

    /// <summary>
    /// 清除代码中的注释
    /// </summary>
    /// <param name="codeTextArr">源代码</param>
    /// <returns>消除注释的源代码</returns>
    private static string ClearComments(string[] codeTextArr)
    {
        var buffer = new StringBuilder();
        foreach (var line in codeTextArr)
        {
            ArgumentNullException.ThrowIfNull(line);
            if (line != string.Empty)
            {
                var str = line.Trim();
                // Debug.WriteLine(nameof(line) + ": " + line);
                // Debug.WriteLine(nameof(str) + ": " + str);
                if (str.Length is < 2 || str[0..2] != "//")
                {
                    buffer.Append(line.Trim());
                }
            }
        }
        return ClearComments(buffer.ToString());
    }

    /// <summary>
    /// 位于有效下标范围内
    /// </summary>
    /// <param name="status"></param>
    /// <returns></returns>
    private bool IsInCodeTextRange(in ScanStatus status)
        => IsInCodeTextRange(status.Point);

    /// <summary>
    /// 位于有效下标范围内
    /// </summary>
    /// <param name="index"></param>
    /// <returns></returns>
    private bool IsInCodeTextRange(in int index)
        => index >= 0 && index < CodeText.Length;


    /// <summary>
    /// 从指定的位置开始分裂出word
    /// </summary>
    /// <param name="codeText"></param>
    /// <param name="first">开始位置</param>
    /// <returns>word，可能是关键词、标识符、常量</returns>
    private static int GetWordLast(in string codeText, int first)
    {
        while (first < codeText.Length && (char.IsLetterOrDigit(codeText[first]) || codeText[first] is '.'))
        {
            first++;
        }
        return first;
    }

    /// <summary>
    /// 获取下一个Token
    /// </summary>
    /// <param name="firstStatus">开始扫描的位置</param>
    /// <param name="lastStatus">结束扫描的位置</param>
    /// <returns>Token</returns>
    public Token NextToken(in ScanStatus firstStatus, out ScanStatus lastStatus)
    {
        /// <summary>
        /// 越界问题
        /// </summary>
        /// <param name="!IsInCodeTextRange(status)"></param>
        /// <returns></returns>
        if (!firstStatus.Available || !IsInCodeTextRange(firstStatus))
        {
            if (CodeText.Length <= firstStatus.Point)
            {
                lastStatus = firstStatus;
                return new(string.Empty, ETokenType.Period);
            }
            else
            {
                throw new ScanStatusPointNotAvaliableException();
            }
        }

        int first = firstStatus.Point;

        while (first < CodeText.Length && CodeText[first] is ' ' or '\t' or '\n')
        {
            first++;
        }
        if (first >= CodeText.Length)
        {
            lastStatus = new ScanStatus(first);
            return new(string.Empty, ETokenType.Period);
        }

        // 标识符 or 变量
        if (char.IsLetterOrDigit(CodeText[first]))
        {
            int last = GetWordLast(CodeText, first);
            string word = CodeText[first..last];

            lastStatus = new ScanStatus(last);

            var wordType = GetKeywordEToken(word);
            if (wordType is not ETokenType.Error)
            {
                return new(word, wordType);
            }
            if (char.IsLetter(word[0]))
            {
                return new(word, ETokenType.Identifier);
            }
            else
            {
                return new(word, ETokenType.Constant);
            }
        }
        else if (CodeText[first] is '\"' or '\'')
        {
            int last = first;
            do
            {
                last = CodeText.IndexOf(CodeText[first], last + 1);
                if (last is -1)
                {
                    throw new CharOrStringNotCloseException("代码字符串未闭合");
                }
                if (CodeText[last - 1] is not '\\')
                {
                    last += 1;
                    string word = CodeText[first..last];
                    lastStatus = new ScanStatus(last);
                    return new(word, ETokenType.Identifier);
                }
            } while (true);
        }

        // 分割符号
        if (TryGetSeparatorEToken(CodeText[first..(first + 1)], out var result))
        {
            lastStatus = new ScanStatus(first + 1);
            return new(CodeText[first..(first + 1)], result);
        }

        // 运算符
        if (first + 2 < CodeText.Length && TryGetOperatorEToken(CodeText[first..(first + 3)], out result))
        {
            lastStatus = new(first + 3);
            return new(CodeText[first..(first + 3)], result);
        }
        if (first + 1 < CodeText.Length && TryGetOperatorEToken(CodeText[first..(first + 2)], out result))
        {
            lastStatus = new(first + 2);
            return new(CodeText[first..(first + 2)], result);
        }
        if (TryGetOperatorEToken(CodeText[first..(first + 1)], out result))
        {
            lastStatus = new(first + 1);
            return new(CodeText[first..(first + 1)], result);
        }

        // WTF
        throw new Exception("WTF");
    }

    /// <summary>
    /// 分析代码
    /// </summary>
    /// <returns>末尾不带终结符的token列表</returns>
    public List<Token> Analyze()
    {
        List<Token> tokens = [];
        ScanStatus first = new(0);
        while (true)
        {
            var result = NextToken(first, out var last);
            if (result.IsPeriod())
            {
                break;
            }
            tokens.Add(result);
            first = last;
        }
        return tokens;
    }

    /// <summary>
    /// 词法分析
    /// </summary>
    /// <param name="code"></param>
    /// <returns>词法分析结果</returns>
    public static List<Token> Analyze(in string code)
        => new LexecalAnalyzer(code).Analyze();

    /// <summary>
    /// 词法分析
    /// </summary>
    /// <param name="code"></param>
    /// <returns>词法分析结果</returns>
    public static List<Token> Analyze(in string[] code)
        => Analyze(ClearComments(code));

    /// <summary>
    /// 检查 word 类型是否在 Keyword 范围内
    /// </summary>
    /// <param name="word">待分析 word</param>
    /// <returns>word 的 Keyword 类型或 error</returns>
    private static ETokenType GetKeywordEToken(in string word)
        => word switch
        {
            "void" => ETokenType.Void,
            "bool" => ETokenType.Bool,
            "char" => ETokenType.Char,
            "short" => ETokenType.Short,
            "int" => ETokenType.Int,
            "float" => ETokenType.Float,
            "double" => ETokenType.Double,
            "if" => ETokenType.If,
            "else" => ETokenType.Else,
            "while" => ETokenType.While,
            "do" => ETokenType.Do,
            "struct" => ETokenType.Struct,
            "return" => ETokenType.Return,
            "const" => ETokenType.Const,
            _ => ETokenType.Error
        };

    private static ETokenType GetOperatorEToken(in string word)
        => word switch
        {
            "+" => ETokenType.Addition,
            "++" => ETokenType.Increment,
            "+=" => ETokenType.AdditionAssignment,
            "-" => ETokenType.Subtraction,
            "--" => ETokenType.Decrement,
            "-=" => ETokenType.SubtractionAssignment,
            "*" => ETokenType.Multiplication,
            "*=" => ETokenType.ModuloAssignment,
            "/" => ETokenType.Division,
            "/=" => ETokenType.DivisionAssignment,
            "%" => ETokenType.Modulo,
            "%=" => ETokenType.ModuloAssignment,

            "=" => ETokenType.BasicAssignment,

            "&" => ETokenType.BitAnd,
            "&=" => ETokenType.BitAndAssignmnet,
            "|" => ETokenType.BitOr,
            "|=" => ETokenType.BitOrAssignmnet,
            "^" => ETokenType.BitXor,
            "^=" => ETokenType.BitXorAssignmnet,
            "<<" => ETokenType.BitLeftShift,
            "<<=" => ETokenType.BitLeftShiftAssignmnet,
            ">>" => ETokenType.BitRightShift,
            ">>=" => ETokenType.BitRightShiftAssignmnet,

            "==" => ETokenType.EqualTo,
            "!=" => ETokenType.NotEqualTo,
            "<" => ETokenType.LessThan,
            "<=" => ETokenType.LessThanOrEqualTo,
            ">" => ETokenType.GreaterThan,
            ">=" => ETokenType.GreaterThanOrEqualTo,

            "!" => ETokenType.LogicalNot,
            "&&" => ETokenType.LogicalAnd,
            "||" => ETokenType.LogicalOr,

            _ => ETokenType.Error,
        };

    private static bool TryGetOperatorEToken(in string word, out ETokenType result)
    {
        result = GetOperatorEToken(word);
        return result is not ETokenType.Error;
    }

    private static ETokenType GetSeparatorEToken(in string word)
        => word switch
        {
            "," => ETokenType.Comma,
            ";" => ETokenType.Semicolon,
            "(" => ETokenType.OpenParentheses,
            ")" => ETokenType.CloseParentheses,
            "{" => ETokenType.OpenBracket,
            "}" => ETokenType.CloseBracket,
            _ => ETokenType.Error
        };

    private static bool TryGetSeparatorEToken(in string word, out ETokenType result)
    {
        result = GetSeparatorEToken(word);
        return result is not ETokenType.Error;
    }
}
