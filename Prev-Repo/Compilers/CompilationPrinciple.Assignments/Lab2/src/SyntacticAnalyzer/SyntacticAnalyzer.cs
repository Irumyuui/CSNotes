using System.Diagnostics;
using System.Runtime.CompilerServices;

namespace Crt.CSyntac;

/// <summary>
/// 分析程序异常
/// </summary>
public class SyntacticErrorException : Exception
{
    public SyntacticErrorException() : base() { }

    public SyntacticErrorException(string? message) : base(message) { }

    public static void Assert(in bool expr, [CallerArgumentExpression(nameof(expr))] string? message = null)
    {
        if (!expr)
        {
            throw new SyntacticErrorException($"{message} is faild.");
        }
    }
}

public class SyntacticAnalyzer
{
    public List<Crt.CLex.Token> TokenList { get; private set; }

    public SyntacticAnalyzer(in Crt.CLex.LexecalAnalyzer lex)
    {
        TokenList = lex.Analyze();
        TokenList.Add(new Crt.CLex.Token(string.Empty, Crt.CLex.ETokenType.Period));
    }

    /// <summary>
    /// 添加调用函数名称
    /// </summary>
    /// <param name="funcList"></param>
    /// <param name="memberName"></param>
    private static void AddTraceFunc(List<string>? funcList, [CallerMemberName] string memberName = "")
    {
        funcList?.Add(memberName);
        if (funcList is not null)
            Console.WriteLine(string.Join(',', funcList));
    }

    /// <summary>
    /// program ::= declaration-list statements
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Program(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsTypeSpecifier())
        {
            DeclarationList(ref first, funcList);
            Statements(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(Program)}: {TokenList[first]} is not type specifier.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// declaration-list ::=var-declaration declaration-list |ε
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void DeclarationList(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsTypeSpecifier())
        {
            VarDeclaration(ref first, funcList);
            DeclarationList(ref first, funcList);
        }
        else
        {
            // nothing need to do in here...
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// var-declaration ::= type-specifier id-list ;
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void VarDeclaration(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsTypeSpecifier())
        {
            TypeSpecifier(ref first, funcList);
            IdList(ref first, funcList);
            if (TokenList[first].IsSemicolon())
            {
                first++;
            }
            else
            {
                throw new SyntacticErrorException($"Error in {nameof(VarDeclaration)}: {TokenList[first]} is not semicolon.");
            }
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(VarDeclaration)}: {TokenList[first]} is not type specifier.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// type-specifier ::= int | double
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void TypeSpecifier(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (!TokenList[first].IsTypeSpecifier())
        {
            throw new SyntacticErrorException($"Error in {nameof(TypeSpecifier)}: {TokenList[first]} is not type specifier.");
        }
        first++;

        funcList?.RemoveLast();
    }

    /// <summary>
    /// id-list ::= ID list-tail
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void IdList(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsIdentifier())
        {
            first++;
            ListTail(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(IdList)}: {TokenList[first]} is not identifier.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// list-tail ::= , ID list-tail |ε
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void ListTail(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsComma())
        {
            first++;
            if (TokenList[first].IsIdentifier())
            {
                first++;
                ListTail(ref first, funcList);
            }
            else
            {
                throw new SyntacticErrorException($"Error in {nameof(ListTail)}: {TokenList[first]} is not identifier.");
            }
        }
        else
        {
            // nothing need to do in here...
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// statements ::= statement ; statements |ε
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Statements(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsIdentifier())
        {
            Statement(ref first, funcList);
            if (TokenList[first].IsSemicolon())
            {
                first++;
                Statements(ref first, funcList);
            }
            else
            {
                throw new SyntacticErrorException($"Error in {nameof(Statements)}: {TokenList[first]} is not semicolon.");
            }
        }
        else
        {
            // nothing need to do in here...
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// statement := assign_statement
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Statement(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsIdentifier())
        {
            AssignStatement(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(Statement)}: {TokenList[first]} is not identifier.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// assign_statement ::= ID = expr
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void AssignStatement(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsIdentifier())
        {
            first++;
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(AssignStatement)}: {TokenList[first]} is not identifier.");
        }

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].IsBasicAssignment())
        {
            first++;
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(AssignStatement)}: {TokenList[first]} is not basic assignment.");
        }

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].TokenType is Crt.CLex.ETokenType.OpenParentheses or Crt.CLex.ETokenType.Identifier or Crt.CLex.ETokenType.Constant)
        {
            Expr(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(AssignStatement)}: {TokenList[first]} is not open parentheses or not identifier or not constant.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// expr ::= term expr1
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Expr(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].TokenType is Crt.CLex.ETokenType.OpenParentheses or Crt.CLex.ETokenType.Identifier or Crt.CLex.ETokenType.Constant)
        {
            Term(ref first, funcList);
            Expr1(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(Expr)}: {TokenList[first]} is not open parentheses or not identifier or not constant.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// term ::= factor term1
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Term(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].TokenType is Crt.CLex.ETokenType.OpenParentheses or Crt.CLex.ETokenType.Identifier or Crt.CLex.ETokenType.Constant)
        {
            Factor(ref first, funcList);
            Term1(ref first, funcList);
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(Term)}: {TokenList[first]} is not open parentheses or not identifier or not constant.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// factor ::= (expr) | ID | NUM
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Factor(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        Debug.WriteLine(TokenList[first]);
        if (TokenList[first].TokenType is Crt.CLex.ETokenType.OpenParentheses)
        {
            first++;
            Expr(ref first, funcList);
            if (TokenList[first].TokenType is Crt.CLex.ETokenType.CloseParentheses)
            {
                first++;
            }
            else
            {
                throw new SyntacticErrorException($"Error in {nameof(Factor)}: {TokenList[first]} is not close parentheses.");
            }
        }
        else if (TokenList[first].TokenType is Crt.CLex.ETokenType.Identifier or Crt.CLex.ETokenType.Constant)
        {
            first++;
        }
        else
        {
            throw new SyntacticErrorException($"Error in {nameof(Factor)}: {TokenList[first]} is not open parentheses or not identifier or not constant.");
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// term1 ::= *factor term1 | /factor term1 | ε
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Term1(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        if (TokenList[first].TokenType is Crt.CLex.ETokenType.Multiplication or Crt.CLex.ETokenType.Division)
        {
            first++;
            Factor(ref first, funcList);
            Term1(ref first, funcList);
        }
        else
        {
            // nothing need to do in here...
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// expr1 ::= +term expr1 | -term expr1 |ε
    /// </summary>
    /// <param name="first"></param>
    /// <param name="funcList"></param>
    private void Expr1(ref int first, List<string>? funcList = null)
    {
        AddTraceFunc(funcList);

        if (TokenList[first].TokenType is Crt.CLex.ETokenType.Addition or Crt.CLex.ETokenType.Subtraction)
        {
            first++;
            Term(ref first, funcList);
            Expr1(ref first, funcList);
        }
        else
        {
            // nothing need to do in here...
        }

        funcList?.RemoveLast();
    }

    /// <summary>
    /// 分析代码
    /// </summary>
    /// <param name="withFuncCallList">是否带有调用信息</param>
    /// <returns>分析结果</returns>
    public bool Analyze(bool withFuncCallList = false)
    {
        int first = 0;
        Program(ref first, withFuncCallList ? [] : null);
        return first < TokenList.Count && TokenList[first].IsPeriod();
    }
}

public static class ListExtendsion
{
    /// <summary>
    /// Check if list is empty.
    /// </summary>
    /// <param name="list"></param>
    /// <typeparam name="T"></typeparam>
    /// <returns>List is empty or not.</returns>
    public static bool IsEmpty<T>(this System.Collections.Generic.List<T> list)
        => list.Count is 0;

    /// <summary>
    /// Removes the element at the specified index of the list.
    /// </summary>
    /// <param name="list"></param>
    /// <param name="index"></param>
    /// <typeparam name="T"></typeparam>
    public static void RemoveAt<T>(this System.Collections.Generic.List<T> list, System.Index index)
        => list.RemoveAt(index.GetOffset(list.Count));

    /// <summary>
    /// Removes the element at the last of the list.
    /// </summary>
    /// <param name="list"></param>
    /// <param name="index"></param>
    /// <typeparam name="T"></typeparam>
    public static void RemoveLast<T>(this System.Collections.Generic.List<T> list)
        => list.RemoveAt(^1);
}
