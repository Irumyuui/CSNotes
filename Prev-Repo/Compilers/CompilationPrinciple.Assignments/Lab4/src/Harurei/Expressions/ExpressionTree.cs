using System;
using System.Collections.Generic;
using System.Linq;

namespace Hakurei.CodeAnalyzer.Expression;

public sealed class ExpressionTree
{
    public ExpressionTree(in string[] text)
    {
        var parser = new Parser(text);
        var tree = parser.Parse();

        Root = tree.Root;
        EndOfFileToken = tree.EndOfFileToken;
        //Diagostics.AddRange(parser.Diagostics);
    }

    public ExpressionTree(ExpressionNode root, SyntaxToken endOfFileToken)
    {
        Root = root;
        EndOfFileToken = endOfFileToken;
    }

    //public List<string> Diagostics { get; private set; } = [];

    public ExpressionNode Root { get; }

    public SyntaxToken EndOfFileToken { get; }

    public EnvironmentSymbolTable Excute()
    {
        var table = new EnvironmentSymbolTable();
        Root.Execute(table);
        return table;
    }

    public void PrettyPrint()
    {
        //Console.WriteLine("Program");
        PrettyPrint(Root);
    }

    private static void PrettyPrint(IExpressionNode node, string indent = "", bool isLast = true)
    {
        // ├─ │ └─

        var marker = isLast ? "└───" : "├───";

        var prevColor = Console.ForegroundColor;

        Console.ForegroundColor = ConsoleColor.Cyan;
        Console.Write(indent);
        Console.Write(marker);
        Console.ForegroundColor = prevColor;


        if (node is SyntaxToken token) {
            prevColor = Console.ForegroundColor;
            Console.ForegroundColor = ConsoleColor.Green;

            Console.Write(" " + node.Kind);

            Console.ForegroundColor = ConsoleColor.Magenta;
            Console.Write($" =>");

            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Write($" Word: \"{token.Word}\";");

            if (token.Value is not null) {
                Console.Write($" {token.Value};");
            }
            Console.Write($" In {token.Line}:{token.Position}");

            Console.ForegroundColor = prevColor;
        } else {
            Console.Write(" " + node.Kind);
        }

        Console.WriteLine();

        indent += isLast ? "    " : "│   ";

        var lastChild = node.GetChildren().LastOrDefault();
        foreach (var child in node.GetChildren())
            PrettyPrint(child, indent, child == lastChild);
    }

    //public static ExpressionTree GetTree(in string[] lines)
    //{
    //    var parser = new Hakurei.CodeAnalyzer.Parser(lines);
    //    var tree = parser.Parse();
    //}
}
