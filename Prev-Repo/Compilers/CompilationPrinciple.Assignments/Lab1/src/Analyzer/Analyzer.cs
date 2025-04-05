using System.Data;
using System.Text.Json;
using System.Text;

namespace Utility;

public class BasicAnalyzerInfo
{
    /// <summary>
    /// 关键词列表
    /// </summary>
    public string[]? Keywords { get; set; }

    /// <summary>
    /// 操作符列表
    /// </summary>
    public string[]? Operators { get; set; }

    /// <summary>
    /// 分隔符列表
    /// </summary>
    public string[]? Separators { get; set; }

    /// <summary>
    /// 字段是否为空
    /// </summary>
    /// <returns></returns>
    public bool NotNullField() => Keywords is not null && Operators is not null && Separators is not null;

    /// <summary>
    /// 序列化为 JSON string
    /// </summary>
    /// <param name="value"></param>
    /// <returns></returns>
    public static string Serialize(BasicAnalyzerInfo value)
        => JsonSerializer.Serialize<BasicAnalyzerInfo>(value);

    /// <summary>
    /// 从 JSON string 中反序列化
    /// </summary>
    /// <param name="jsonString"></param>
    /// <returns></returns>
    public static BasicAnalyzerInfo? Deserialize(string jsonString)
        => JsonSerializer.Deserialize<BasicAnalyzerInfo>(jsonString);

    /// <summary>
    /// 从 JSON 中反序列化
    /// </summary>
    /// <param name="jsonFileName"></param>
    /// <returns></returns>
    public static BasicAnalyzerInfo? DeserializeFromFile(string jsonFileName)
        => JsonSerializer.Deserialize<BasicAnalyzerInfo>(File.ReadAllText(jsonFileName));

    public override string ToString()
        =>
$@"{{
    Keywords: [{(Keywords is null ? "" : string.Join(',', Keywords))}]; 
    Operators: [{(Operators is null ? "" : string.Join(',', Operators))}]; 
    Separators: [{(Separators is null ? "" : string.Join(',', Separators.Select(x => $"\"{x}\"")))}]
}}";
}

/// <summary>
/// 扫描结果
/// </summary>
public struct LexerAnalyzerResultItem
{
    /// <summary>
    /// 码
    /// </summary>
    public int TokenType { get; set; }

    /// <summary>
    /// 值
    /// </summary>
    public string? Attribute { get; set; }

    public LexerAnalyzerResultItem(int categoryCode, string? value)
    {
        TokenType = categoryCode;
        Attribute = value;
    }

    public override readonly string ToString()
        => $"({TokenType}, {(Attribute is null ? " " : Attribute)})";
}

/// <summary>
/// 结束状态
/// </summary>
public class LexerAnalyzerResult
{
    public List<LexerAnalyzerResultItem> ItemList { get; set; }

    public LexerAnalyzerResultItem this[int index]
    {
        get => ItemList[index];
        set => ItemList[index] = value;
    }

    public LexerAnalyzerResult()
        => ItemList = new();

    public void Add(in LexerAnalyzerResultItem item) => ItemList.Add(item);

    /// <summary>
    /// 清空
    /// </summary>
    public void Clear() => ItemList.Clear();
}

/// <summary>
/// Token 类别
/// </summary>
public enum ETokenType
{
    /// <summary>
    /// 标识符
    /// </summary>
    Identifier,

    /// <summary>
    /// 常量
    /// </summary>
    Constant,

    /// <summary>
    /// 保留字，关键字
    /// </summary>
    Keyword,

    /// <summary>
    /// 操作符
    /// </summary>
    Operator,

    /// <summary>
    /// 分隔符
    /// </summary>
    Separator,

    /// <summary>
    /// 错误
    /// </summary>
    Error
};

public class ScannerStatus
{
    /// <summary>
    /// 左小括号数量
    /// </summary>
    private int _leftParenthesesCount;

    /// <summary>
    /// 是否出现右括号错误
    /// </summary>
    private bool _leftParenthesesCountHasNegativeNumber;

    /// <summary>
    /// 左小括号数量
    /// </summary>
    public int LeftParenthesesCount
    {
        get => _leftParenthesesCount;
        set
        {
            _leftParenthesesCount = value;
            if (_leftParenthesesCount < 0)
            {
                _leftParenthesesCountHasNegativeNumber = true;
            }
        }
    }

    /// <summary>
    /// 左中括号数量
    /// </summary>
    private int _leftBracketsCount;

    /// <summary>
    /// 是否出现右中括号不匹配
    /// </summary>
    private bool _leftBracketsCountHasNegativeNumber;

    /// <summary>
    /// 左中括号数量
    /// </summary>
    public int LeftBracketsCount
    {
        get => _leftBracketsCount;
        set
        {
            _leftBracketsCount = value;
            if (_leftBracketsCount < 0)
            {
                _leftBracketsCountHasNegativeNumber = true;
            }
        }
    }

    /// <summary>
    /// 左大括号
    /// </summary>
    private int _leftBraceCount;

    /// <summary>
    /// 左大括号
    /// </summary>
    private bool _leftBraceCountHasNegativeNumber;

    // where is the stack?

    /// <summary>
    /// 左大括号数量
    /// </summary>
    public int LeftBraceCount
    {
        get => _leftBraceCount;
        set
        {
            _leftBraceCount = value;
            if (_leftBraceCount < 0)
            {
                _leftBraceCountHasNegativeNumber = true;
            }
        }
    }

    /// <summary>
    /// 源代码
    /// </summary>
    public string CodeText { get; }

    /// <summary>
    /// 扫描指针
    /// </summary>
    public int Peek { get; set; }

    /// <summary>
    /// 结束列表
    /// </summary>
    public LexerAnalyzerResult ResultList { get; set; }

    /// <summary>
    /// 指针指向的字符
    /// </summary>
    public char FristChar => CodeText[Peek];

    /// <summary>
    /// 小括号是否匹配
    /// </summary>
    public bool ParenthesesNoMatch => LeftParenthesesCount != 0 || _leftParenthesesCountHasNegativeNumber;

    /// <summary>
    /// 中括号是否匹配
    /// </summary>
    public bool BracketsNoMatch => LeftBracketsCount != 0 || _leftBracketsCountHasNegativeNumber;

    /// <summary>
    /// 大括号是否匹配
    /// </summary>
    public bool BraceNoMatch => LeftBraceCount != 0 || _leftBraceCountHasNegativeNumber;

    /// <summary>
    /// 源代码
    /// </summary>
    /// <param name="codeText"></param>
    /// <exception cref="ArgumentNullException">codeText is not null</exception>
    public ScannerStatus(string? codeText)
    {
        CodeText = codeText ?? throw new ArgumentNullException(nameof(codeText));
        ResultList = new();
        Peek = 0;

        _leftParenthesesCount = 0;
        _leftParenthesesCountHasNegativeNumber = false;

        _leftBracketsCount = 0;
        _leftBracketsCountHasNegativeNumber = false;

        _leftBraceCount = 0;
        _leftBraceCountHasNegativeNumber = false;
    }

    public static bool IsEndChar(char? x)
        => x is null or '}' or ';';

    /// <summary>
    /// 判断是否是 10 进制
    /// </summary>
    /// <param name="token"></param>
    /// <returns></returns>
    public static bool IsDigitString(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;

        if (!char.IsDigit(token[0]))
        {
            if (token[0] is not '+' and not '-' || token.Length > 1)
            {
                return false;
            }
            for (int i = 1; i < token.Length; i++)
            {
                if (!char.IsDigit(token[i]))
                {
                    return false;
                }
            }
            return true;
        }
        for (int i = 0; i < token.Length; i++)
        {
            if (!char.IsDigit(token[i]))
            {
                return false;
            }
        }

        return true;
    }

    /// <summary>
    /// 是常量吗
    /// </summary>
    /// <param name="token"></param>
    /// <returns></returns>
    public static bool IsConstant(string? token)
    {
        if (string.IsNullOrEmpty(token))
        {
            return false;
        }
        if (IsDigitString(token))
        {
            return true;
        }
        if (token[0] == token[^1] && token[0] is '\'' or '"')
        {
            return true;
        }

        return false;
    }

    /// <summary>
    /// 清除状态
    /// </summary>
    public void ResetStatus()
    {
        ResultList.Clear();
        Peek = 0;
        _leftParenthesesCount = 0;
        _leftParenthesesCountHasNegativeNumber = false;
        _leftBracketsCount = 0;
        _leftBracketsCountHasNegativeNumber = false;
        _leftBraceCount = 0;
        _leftBraceCountHasNegativeNumber = false;
    }
}

public class LexerAnalyzer
{

    /// <summary>
    /// 常数表
    /// 动态添加
    /// 0 0x23
    /// </summary>
    // private Dictionary<string,int> _constant;

    /// <summary>
    /// 保留字
    /// </summary>
    public Dictionary<string, int> Keywords { get; }

    /// <summary>
    /// 运算符
    /// </summary>
    public Dictionary<string, int> Operators { get; }

    /// <summary>
    /// 分割符
    /// </summary>
    public Dictionary<string, int> Separators { get; }


    /// <summary>
    /// 标识符与常量
    /// </summary>
    public Dictionary<string, int> Constant { get; set; }

    public Dictionary<string, int> Identifier { get; set; }

    /// <summary>
    /// 扫描器状态
    /// </summary>
    public ScannerStatus? Scanner { get; set; }

    public LexerAnalyzer(in BasicAnalyzerInfo? value)
    {
        ArgumentNullException.ThrowIfNull(value);
        ArgumentNullException.ThrowIfNull(value.Keywords);
        ArgumentNullException.ThrowIfNull(value.Operators);
        ArgumentNullException.ThrowIfNull(value.Separators);

        Keywords = value.Keywords
                         .DistinctBy(x => x)
                         .Select((value, index) => new { value, index })
                         .ToDictionary(pair => pair.value, pair => pair.index);

        Operators = value.Operators
                          .DistinctBy(x => x)
                          .Select((value, index) => new { value, index = index + Keywords.Count })
                          .ToDictionary(pair => pair.value, pair => pair.index);

        Separators = value.Separators
                           .DistinctBy(x => x)
                           .Select((value, index) => new { value, index = index + Keywords.Count + Operators.Count })
                           .ToDictionary(pair => pair.value, pair => pair.index);

        Constant = new Dictionary<string, int>();
        Identifier = new Dictionary<string, int>();

        Scanner = null;
    }

    public override string ToString()
        =>
$@"{{
    Keywords: {{{string.Join(',', Keywords)}}};
    Operators: {{{string.Join(',', Operators)}}};
    Separators: {{{string.Join(',', Separators)}}};
    Constant: {{{string.Join(',', Constant)}}};
    Identifier: {{{string.Join(',', Identifier)}}}
}}";

    public bool ContainsKeywordsList(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;
        return Keywords.ContainsKey(token);
    }

    public bool ContainsOperatorsList(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;
        return Operators.ContainsKey(token);
    }

    public bool ContainsSeparatorsList(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;
        return Separators.ContainsKey(token);
    }

    public bool ContainsConstantList(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;
        return Constant.ContainsKey(token);
    }

    public bool ContainsIdentifierList(string? token)
    {
        if (string.IsNullOrEmpty(token))
            return false;
        return Identifier.ContainsKey(token);
    }

    /// <summary>
    /// 从已经预处理过的代码加载 Scanner
    /// </summary>
    /// <param name="pretreatmentSourceCodeText"></param>
    public void ScannerLoadPretreatmentSourceCodeText(string? pretreatmentSourceCodeText)
    {
        ArgumentNullException.ThrowIfNull(pretreatmentSourceCodeText);
        Scanner = new ScannerStatus(pretreatmentSourceCodeText);
    }

    /// <summary>
    /// 从JSON文件中创建对象
    /// </summary>
    /// <param name="jsonFilePath"></param>
    /// <returns></returns>
    public static LexerAnalyzer ReadWithJsonFile(string? jsonFilePath)
    {
        ArgumentNullException.ThrowIfNull(jsonFilePath);
        return new LexerAnalyzer(BasicAnalyzerInfo.DeserializeFromFile(jsonFilePath));
    }

    /// <summary>
    /// 分析
    /// </summary>
    /// <param name="itemWithWodr"></param>
    /// <exception cref="NoNullAllowedException"></exception>
    public void StarAnalyzer(bool itemWithWodr = false)
    {
        if (Scanner is null)
        {
            throw new NoNullAllowedException(nameof(Scanner));
        }

        // 初始化
        ClearConstantAndIdentifierIdList();
        Scanner.ResetStatus();

        string? token = null;
        while ((token = TakeNextToken()) is not null)
        {
#if DEBUG
            System.Console.Error.WriteLine($"In Alanyzer {token}");
#endif
            System.Diagnostics.Debug.WriteLine($"In Alanyzer {token}");

            var item = GetTokenAnalyzeResult(token, itemWithWodr);
            Scanner.ResultList.Add(item);
        }
    }

    /// <summary>
    /// 获取接下来的第一个词
    /// 包括单词、数字、字符串
    /// </summary>
    /// <returns></returns>
    public string? TakeNextToken()
    {
        if (Scanner is null)
            throw new NoNullAllowedException(nameof(Scanner));

        // 处理掉空格
        while (Scanner.Peek < Scanner.CodeText.Length)
        {
            if (char.IsWhiteSpace(Scanner.CodeText, Scanner.Peek))
            {
                ++Scanner.Peek;
            }
            else
            {
                break;
            }
        }
        if (Scanner.Peek == Scanner.CodeText.Length)
        {
            return null;
        }

        string? token = null;
        int last = Scanner.Peek;

        // 处理单双引号
        if (Scanner.FristChar is '"' or '\'')
        {
            var target = Scanner.FristChar;
            bool isChar = false, ok = false;
            last++;
            // 字符串或字符内的内容
            while (last < Scanner.CodeText.Length)
            {
                var x = Scanner.CodeText[last];
                if (x == target && !isChar)
                {
                    ok = true;
                    last++;
                    break;
                }
                isChar = x == '\\' && !isChar;
                last++;
            }
            // 是否配对
            if (!ok)
            {
                throw new Exception($"No match target {target}.");
            }
            token = Scanner.CodeText[Scanner.Peek..last];
            Scanner.Peek = last;
            return token;
        }

        // 变量 类型 关键字
        if (char.IsAsciiLetter(Scanner.FristChar) || char.IsAsciiDigit(Scanner.FristChar))
        {
            while (last < Scanner.CodeText.Length && !char.IsWhiteSpace(Scanner.CodeText[last]))
            {
                var x = Scanner.CodeText[last];
                var tmp = x.ToString();
                if (Operators.ContainsKey(tmp) || Separators.ContainsKey(tmp))
                {
                    break;
                }
                if (!char.IsAsciiLetter(x) && !char.IsAsciiDigit(x))
                {
                    throw new Exception($"No such ASCII char like {x}.");
                }
                last++;
            }
            token = Scanner.CodeText[Scanner.Peek..last];
            Scanner.Peek = last;
            return token;
        }

        // 小括号
        if (Scanner.FristChar is '(')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftParenthesesCount++;
            return res;
        }
        if (Scanner.FristChar is ')')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftParenthesesCount--;
            return res;
        }

        // 中括号
        if (Scanner.FristChar is '[')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftBracketsCount++;
            return res;
        }
        if (Scanner.FristChar is ']')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftBracketsCount--;
            return res;
        }

        // 大括号
        if (Scanner.FristChar is '{')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftBraceCount++;
            return res;
        }
        if (Scanner.FristChar is '}')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            Scanner.LeftBraceCount--;
            return res;
        }

        // 运算符
        if (Scanner.FristChar is ',' or ';' or '.' or '?' or ':')
        {
            var res = Scanner.FristChar.ToString();
            Scanner.Peek++;
            return res;
        }

        // +123 -123
        if (Scanner.FristChar is '+' or '-' && Scanner.Peek + 1 < Scanner.CodeText.Length && char.IsAsciiDigit(Scanner.CodeText[Scanner.Peek + 1]))
        {
            last = Scanner.Peek + 1;
            while (last < Scanner.CodeText.Length && !char.IsWhiteSpace(Scanner.CodeText[last]))
            {
                var x = Scanner.CodeText[last];
                var tmp = x.ToString();
                if (Operators.ContainsKey(tmp) || Separators.ContainsKey(tmp))
                {
                    break;
                }
                if (!char.IsAsciiLetter(x) && !char.IsAsciiDigit(x))
                {
                    throw new Exception($"No such ASCII char like {x}.");
                }
                last++;
            }
            token = Scanner.CodeText[Scanner.Peek..last];
            Scanner.Peek = last;
            return token;
        }

        if (Operators.ContainsKey(Scanner.FristChar.ToString()))
        {
            var tmp = Scanner.FristChar.ToString();
            if (Scanner.Peek + 1 >= Scanner.CodeText.Length)
            {
                Scanner.Peek++;
                return tmp;
            }

            if (Scanner.Peek + 3 <= Scanner.CodeText.Length)
            {
                var tmp3 = Scanner.CodeText[Scanner.Peek..(Scanner.Peek + 3)];
                if (Operators.ContainsKey(tmp3))
                {
                    Scanner.Peek += 3;
                    return tmp3;
                }
            }

            var tmp2 = Scanner.CodeText[Scanner.Peek..(Scanner.Peek + 2)];
            if (Operators.ContainsKey(tmp2))
            {
                Scanner.Peek += 2;
                return tmp2;
            }

            Scanner.Peek++;
            return tmp;
        }

        throw new Exception("不可能到达");
        // throw new 
    }

    /// <summary>
    /// 预处理源代码文本
    /// </summary>
    /// <param name="sourceCodeText">源代码文本</param>
    /// <returns>处理后的源代码文本</returns>
    public static string PretreatmentSourceCodeText(string[]? sourceCodeText)
    {
        ArgumentNullException.ThrowIfNull(sourceCodeText);

        StringBuilder builder = new();
        foreach (var preLine in sourceCodeText)
        {
            if (preLine is null)
            {
                continue;
            }
            var line = preLine.Trim();
            int inlineNotePos = line.IndexOf("//");
            if (inlineNotePos != -1)
            {
                if (inlineNotePos == 0)
                {
                    continue;
                }
                line = line[..(inlineNotePos - 1)];
            }
            builder.Append(line);
            builder.Append(' ');
        }
#if DEBUG
        System.Console.Error.WriteLine(builder.ToString());
#endif
        return DropMultiNote(builder.ToString());
    }

    /// <summary>
    /// 处理多行注释
    /// </summary>
    /// <param name="sourceCodeText"></param>
    /// <returns></returns>
    public static string DropMultiNote(string? sourceCodeText)
    {
        ArgumentNullException.ThrowIfNull(sourceCodeText);
        StringBuilder builder = new();

        // delete mulitline note
        int first = sourceCodeText.IndexOf("/*"), last = 0;
#if DEBUG
        Console.Error.WriteLine($"First: {first} Last: {last}");
#endif
        while (first != -1)
        {
            builder.Append(sourceCodeText[last..first]);
            last = sourceCodeText.IndexOf("*/", first);
#if DEBUG
            Console.Error.WriteLine($"First: {first} Last: {last}");
#endif
            if (last != -1 && last + 2 < sourceCodeText.Length)
            {
                last += 2;
                first = sourceCodeText.IndexOf("/*", last);
            }
            else
            {
                break;
            }
        }
        if (last != -1 && last < sourceCodeText.Length)
        {
            builder.Append(sourceCodeText[last..]);
        }

        return builder.ToString();
    }

    /// <summary>
    /// 判断 token 类型
    /// </summary>
    /// <param name="token"></param>
    /// <returns></returns>
    public ETokenType GetTokenKind(string? token)
    {
        // 判断空
        if (string.IsNullOrEmpty(token))
        {
            return ETokenType.Error;
        }

        // 是否是标识符号
        if (ContainsKeywordsList(token))
        {
            return ETokenType.Keyword;
        }

        // 是否是操作符
        if (ContainsOperatorsList(token))
        {
            return ETokenType.Operator;
        }

        // 是否是分割符
        if (ContainsSeparatorsList(token))
        {
            return ETokenType.Separator;
        }

        // 常量或标识符
        if (ScannerStatus.IsConstant(token))
        {
#if DEBUG
            System.Console.Error.WriteLine($"Constant: {token}");
#endif
            TryGetConstantId(token);
            return ETokenType.Constant;
        }
#if DEBUG
        System.Console.Error.WriteLine($"Identifier: {token}");
#endif
        TryGetIdentifierId(token);
        return ETokenType.Identifier;
    }

    /// <summary>
    /// 清除列表
    /// </summary>
    private void ClearConstantAndIdentifierIdList()
    {
        Constant.Clear();
        Identifier.Clear();
    }

    private int TryGetConstantId(string token)
    {
#if DEBUG
        System.Console.Error.WriteLine($"TryGetConstantId: {token}");
#endif
        if (string.IsNullOrEmpty(token))
        {
            return -1;
        }
        if (Constant.TryGetValue(token, out int value))
        {
            return value;
        }
        int newid = Keywords.Count
            + Operators.Count
            + Separators.Count
            + Constant.Count
            + Identifier.Count;
        Constant.Add(token, newid);
        return newid;
    }

    private int TryGetIdentifierId(string token)
    {
#if DEBUG
        System.Console.Error.WriteLine($"TryGetIdentifierId: {token}");
#endif
        if (string.IsNullOrEmpty(token))
        {
            return -1;
        }
        if (Identifier.TryGetValue(token, out int value))
        {
            return value;
        }
        int newid = Keywords.Count
            + Operators.Count
            + Separators.Count
            + Constant.Count
            + Identifier.Count;
        Identifier.Add(token, newid);
        return newid;
    }

    /// <summary>
    /// 获取 word 类别
    /// </summary>
    /// <param name="token"></param>
    /// <returns></returns>
    public LexerAnalyzerResultItem GetTokenAnalyzeResult(string token, bool witnToken = false)
        => GetTokenKind(token) switch
        {
            ETokenType.Keyword => new(Keywords[token], witnToken ? token : null),
            ETokenType.Operator => new(Operators[token], witnToken ? token : null),
            ETokenType.Separator => new(Separators[token], witnToken ? token : null),
            ETokenType.Constant => new(TryGetConstantId(token), token),
            ETokenType.Identifier => new(TryGetIdentifierId(token), token),
            _ => new(-1, witnToken ? token : "ERROR"),
        };

    /// <summary>
    /// 结果序列转为 List<string>
    /// </summary>
    /// <returns></returns>
    /// <exception cref="NoNullAllowedException"></exception>
    public List<string> GetResultList()
    {
        if (Scanner is null)
        {
            throw new NoNullAllowedException(nameof(Scanner));
        }

        var table = Scanner.ResultList.ItemList.Select(item => item.ToString()).ToList();
        return table;
    }

    public List<string> GetResult()
    {
        if (Scanner is null)
            throw new NoNullAllowedException(nameof(Scanner));

        var list = GetResultList();
        if (Scanner.ParenthesesNoMatch)
        {
            // System.Console.WriteLine("存在小括号没有匹配");
            list.Add("Waring: 存在小括号没有匹配");
        }
        if (Scanner.BracketsNoMatch)
        {
            // System.Console.WriteLine("存在中括号没有匹配");
            list.Add("Waring: 存在中括号没有匹配");
        }
        if (Scanner.BraceNoMatch)
        {
            // System.Console.WriteLine("存在大括号没有匹配");
            list.Add("Waring: 存在大括号没有匹配");
        }

        return list;
    }

    /// <summary>
    /// 直接打印结果
    /// </summary>
    /// <exception cref="NoNullAllowedException"></exception>
    public void PrintResult()
        => GetResult().ForEach(System.Console.WriteLine);

    /// <summary>
    /// 输出至文件中
    /// </summary>
    /// <param name="filePath"></param>
    /// <exception cref="ArgumentNullException"></exception>
    public void WriteFile(string? filePath)
    {
        ArgumentException.ThrowIfNullOrEmpty(filePath);
        File.WriteAllLines(filePath, GetResult(), Encoding.UTF8);
    }
}
