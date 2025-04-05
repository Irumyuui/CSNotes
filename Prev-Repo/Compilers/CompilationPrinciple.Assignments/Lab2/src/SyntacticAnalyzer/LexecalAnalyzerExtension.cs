using Crt.CLex;

namespace Crt.CSyntac;

public static partial class LexecalAnalyzerExtension
{
    public static Token NextToken(this LexecalAnalyzer lex, ref ScanStatus status)
    {
        var token = lex.NextToken(status, out var lastStatus);
        status = lastStatus;
        return token;
    }

    public static void NextToken(this LexecalAnalyzer lex, ref ScanStatus status, out Token result)
    {
        var token = lex.NextToken(status, out var lastStatus);
        status = lastStatus;
        result = token;
    }
}
