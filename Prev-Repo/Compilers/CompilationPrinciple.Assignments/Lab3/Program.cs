using System;
using System.Collections.Generic;
using System.CommandLine;
using System.Data;
using System.Linq;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Threading;
using System.Threading.Tasks;
using System.Xml.Schema;
using Hakurei;

internal class Program
{
#if !DEBUG
    private static async Task<int> Main(string[] args)
    {
        var rootCommand = new System.CommandLine.RootCommand("Parse.");

        var fileOption = new System.CommandLine.Option<string?>(
            name: "--file",
            description: "The grama file path. Not ignore spaces."
        )
        {
            IsRequired = true
        };
        fileOption.AddValidator(result =>
        {
            string? filePath = result.GetValueForOption(fileOption);
            if (filePath is null || !System.IO.File.Exists(filePath))
            {
                result.ErrorMessage = $"Invalid file path: {filePath}";
            }
        });

        var outputOption = new System.CommandLine.Option<string>(
            name: "--begin",
            description: "Begin symbol."
        )
        {
            IsRequired = true
        };
        outputOption.AddValidator(result =>
        {
            string? opt = result.GetValueForOption(outputOption);
            if (string.IsNullOrEmpty(opt))
            {
                result.ErrorMessage = $"Invalid type : {opt}";
            }
        });

        rootCommand.AddOption(fileOption);
        rootCommand.AddOption(outputOption);

        rootCommand.SetHandler((file, beginSymbol) => BeginAnalyzer(file!, new SyntaxSymbolNode(beginSymbol)), fileOption, outputOption);

        return await rootCommand.InvokeAsync(args);
    }
#endif

#if DEBUG
    private static void Main(string[] args) {
        string[] lines = [
            "<S>::=<A><B>",
            "<A>::=<D>a",
            "<A>::=",
            "<B>::=c<C>",
            "<C>::=a<A><D>C",
            "<C>::=",
            "<D>::=b",
            "<D>::=",
        ];
        Solution(lines, new SyntaxSymbolNode("S"));
    }
#endif

    // private static void Main(string[] args)
    private static void BeginAnalyzer(string file, SyntaxSymbolNode beginSymbol)
    {
        string[] lines = System.IO.File.ReadAllLines(file)
                                       .Where(line => !string.IsNullOrEmpty(line))
                                       .ToArray();
        Solution(lines, beginSymbol);
    }

    private static void Solution(string[] lines, SyntaxSymbolNode beginSymbol)
    {
        // Format like:
        //      // Do not ignore spaces.
        //     "<S>::=<E>",
        //     "<E>::=<E>+<T>",
        //     "<E>::=<E>-<T>",
        //     "<E>::=<T>",
        //     "<T>::=<T>*<F>",
        //     "<T>::=<T>/<F>",
        //     "<T>::=<F>",
        //     "<F>::=(<E>)",
        //     "<F>::=<id>",

        // List<string> inputLine = [];

        // string[] lines = [.. inputLine];

        var action = (string? heading, Action act) =>
        {
            if (heading is not null)
                Console.WriteLine(heading);
            act();
            Console.WriteLine();
        };

        // 读入 => 消除间接左递归 => 消除直接左递归 => 提取左公因子 => 求FIRST => 求FOLLOW => 判断是否符合LL(1) => 开判

        try
        {
            var res = new SentenceGraph(
                // new SyntaxSymbolNode("E"),
                beginSymbol,
                lines.Select(line => new Sentence(line))
            );
            res.PrettyPrintSentences();
            Console.WriteLine();

            action("Remove1", () =>
            {
                res.RemoveIndirectLeftRecursion();
                res.PrettyPrintSentences();
            });

            action("Remove2:", () =>
            {
                res.RemoveDirectLeftRecursion();
                res.PrettyPrintSentences();
            });

            action(
                "Calc",
                () =>
                {
                    res.ExtractCommonFactors();
                    res.PrettyPrintSentences();
                }
            );

            action(
                "Get frist set",
                () =>
                {
                    res.CalculateFirstSet();
                    res.PrettyPrintFirstSet();
                }
            );

            action(
                "Get Follow set",
                () =>
                {
                    res.CalculateFollowSet();
                    res.PrettyPrintFollowSet();
                }
            );

            action(
                "Is LL(1)?",
                () =>
                {
                    var result = res.MatchLL1();
                    Console.WriteLine(result);
                    if (!result) {
                        System.Environment.Exit(-1);
                    }
                }
            );

            action(
                "Get Table",
                () =>
                {
                    res.CalculateTable();
                    res.PrettyPrintTable();
                }
            );

            var parser = new Parser(res);
            action(
                // "Input \"$\" to finish.",
                null,
                () =>
                {
                    while (true)
                    {
                        Console.WriteLine("Input \"$\" to finish.");
                        Console.Write("> ");
                        var line = Console.ReadLine();
                        if (string.IsNullOrEmpty(line))
                            line = string.Empty;
                        if (line is "$")
                            return;

                        SentenceRightList sentence = new SentenceRightList(line);

                        bool result = false;
                        List<ParserDiagnosticsItem>? list = null;

                        try
                        {
                            result = parser.Parse(sentence, out list);
                        }
                        catch (Exception e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        finally
                        {
                            Console.WriteLine($"Result: {result}.");
                            if (list is not null)
                                ParserDiagnosticsItem.PrettyPrint(list);
                        }
                    }
                }
            );

        }
        catch (System.Exception e)
        {
            Console.WriteLine(e);
        }
    }
}
