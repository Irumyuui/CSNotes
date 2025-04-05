using System;
using System.Collections.Generic;
using System.Linq;
using ConsoleTables;

namespace Hakurei;

public readonly record struct ParserDiagnosticsItem
{
    public ParserDiagnosticsItem(System.Collections.Generic.Stack<SyntaxSymbolNode> stack, SyntaxSymbolNode current, Hakurei.Sentence? sentence = null)
    {
        StackList = stack.Reverse().ToList();
        Current = current;
        Sentence = sentence;
    }
    public System.Collections.Generic.List<SyntaxSymbolNode> StackList { get; }
    public SyntaxSymbolNode Current { get; }
    public Sentence? Sentence { get; }

    public static void PrettyPrint(in List<ParserDiagnosticsItem> result)
    {
        var table = new ConsoleTable(
            "Stack", "Current", "Sentence"
        );
        foreach (var (StackList, Current, Sentence) in result)
        {
            string[] line = [
                string.Concat(StackList), Current.ToString(), Sentence?.ToString() ?? ""
            ];
            table.AddRow(line);
        }
        table.Write();
        Console.WriteLine();
    }

    private void Deconstruct(out System.Collections.Generic.List<SyntaxSymbolNode> stackList, out SyntaxSymbolNode current, out Sentence? sentence)
    {
        stackList = StackList;
        current = Current;
        sentence = Sentence;
    }
}

public class Parser
{
    public Parser(SentenceGraph graph)
    {
        ArgumentNullException.ThrowIfNull(graph.Table);
        Graph = graph;
    }

    public SentenceGraph Graph { get; private set; }

    // TODO
    public bool Parse(SentenceRightList preSentenceList, out List<ParserDiagnosticsItem>? matchList)
    {
        matchList = null;

        if (preSentenceList.Count is 0)
            return true;

        matchList = [];

        Stack<SyntaxSymbolNode> stack = [];
        stack.Push(SyntaxSymbolNode.End);
        stack.Push(Graph.BeginSymbol);

        int position = 0;
        var Next = () =>
        {
            position++;
        };
        var Current = () =>
        {
            if (position >= preSentenceList.Count)
                return SyntaxSymbolNode.End;
            return preSentenceList[position];
        };
        var Success = () => Current() == SyntaxSymbolNode.End;

        matchList.Add(new ParserDiagnosticsItem(stack, Current()));

        while (stack.Count is not 0)
        {
            if (!Graph.IsNoterminalSymbol(Current()) && !Graph.IsTerminalSymbol(Current()))
            {
                throw new Exception($"Unkown symbol: {Current()}");
            }
            if (Current() == stack.Peek())
            {
                stack.Pop();
                Next();
                matchList.Add(new ParserDiagnosticsItem(stack, Current()));
                continue;
            }
            else if (stack.Peek() == SyntaxSymbolNode.Empty)
            {
                stack.Pop();
                matchList.Add(new ParserDiagnosticsItem(stack, Current()));
                continue;
            }
            else if (Graph.IsTerminalSymbol(stack.Peek()))
            {
                throw new Exception($"Expect {stack.Peek()}, found {Current()}.");
            }

            if (Graph.Table!.Table[stack.Peek()].TryGetValue(Current(), out var result))
            {
                if (result is -1)
                    throw new Exception($"In Table[{stack.Peek()}, {Current()}] can not found expect expression.");

                var sentence = Graph.Table.Sentences[result];
                stack.Pop();
                foreach (var item in sentence.Right.Reverse())
                    stack.Push(item);

                matchList.Add(new ParserDiagnosticsItem(stack, Current(), sentence));
            }
            else
            {
                throw new Exception($"In Table can not found such [{stack.Peek()}, {Current()}].");
            }
        }

        return Success();
    }
}
