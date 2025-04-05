using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.CompilerServices;
using ConsoleTables;

namespace Hakurei;

// public class PredictiveAnalysisTableRow :  IEnumerable {
//     public PredictiveAnalysisTableRow(Dictionary<SyntaxSymbol, Sentence> line) => Line = line.ToDictionary();

//     public Dictionary<SyntaxSymbol, Sentence> Line { get; set; }

//     public IEnumerator GetEnumerator()
//     {
//         return (Line as IEnumerable).GetEnumerator();
//     }
// }

public class PredictiveAnalysisTable
{
    public PredictiveAnalysisTable(SentenceGraph graph)
    {
        Sentences = graph.GetSentences();
        TerminalSymbolList = graph.TerminalSymbolList.Where(item => !item.IsEmptySymbol())
                                                     .ToList();
        TerminalSymbolList.Add(new SyntaxSymbolNode("$"));
        NoterminalSymbolList = [.. graph.NoterminalSymbolList];

        Table = [];
        foreach (var sym in NoterminalSymbolList)
            Table.Add(sym, TerminalSymbolList.ToDictionary(item => item, _ => -1));

        FirstSet = graph.FirstSet.ToDictionary();
        FollowSet = graph.FollowSet.ToDictionary();

        TerminalSymbolSet = [.. TerminalSymbolList];
        NoterminalSymbolSet = [.. NoterminalSymbolList];
    }

    public List<Sentence> Sentences { get; private set; }

    public List<SyntaxSymbolNode> TerminalSymbolList { get; private set; }

    public List<SyntaxSymbolNode> NoterminalSymbolList { get; private set; }

    private HashSet<SyntaxSymbolNode> TerminalSymbolSet { get; set; }

    private HashSet<SyntaxSymbolNode> NoterminalSymbolSet { get; set; }

    public Dictionary<SyntaxSymbolNode, Dictionary<SyntaxSymbolNode, int>> Table { get; private set; }

    public Dictionary<SyntaxSymbolNode, SymbolSet> FirstSet { get; private set; }

    public Dictionary<SyntaxSymbolNode, SymbolSet> FollowSet { get; private set; }

    private bool IsTerminalSymbol(SyntaxSymbolNode symbol) => TerminalSymbolSet.Contains(symbol);

    private bool IsNoterminalSymbol(SyntaxSymbolNode symbol) => NoterminalSymbolSet.Contains(symbol);

    public void CalculateTable()
    {
        for (int i = 0; i < Sentences.Count; i++)
        {
            var sentence = Sentences[i];
            var rightFirst = sentence.Right.First;

            if (FirstSet[rightFirst].Contains(SyntaxSymbolNode.Empty))
            {
                foreach (var sym in FollowSet[sentence.Left])
                    if (!sym.IsEmptySymbol() && IsTerminalSymbol(sym))
                        Table[sentence.Left][sym] = i;
            }
            else
            {
                foreach (var fsym in FirstSet[rightFirst])
                    if (!fsym.IsEmptySymbol() && IsTerminalSymbol(fsym))
                        Table[sentence.Left][fsym] = i;
            }

            // PrettyPrint();
        }
    }

    public void PrettyPrint()
    {
        var exprTable = new ConsoleTable("Id", "Expression");
        for (int i = 0; i < Sentences.Count; i++)
        {
            exprTable.AddRow([i.ToString(), Sentences[i].ToString()]);
        }
        exprTable.Write();
        Console.WriteLine();

        string[] heading = ["NoterminalSymbol", .. TerminalSymbolList.Select(item => item.ToString())];

        var tableTable = new ConsoleTable(
            ["NoterminalSymbol", .. TerminalSymbolList.Select(item => item.ToString())]
        );
        foreach (var (key, value) in Table)
        {
            List<string> rowList = [key.ToString()];
            foreach (var item in TerminalSymbolList)
                rowList.Add(value[item] == -1 ? string.Empty : value[item].ToString());
            tableTable.AddRow(rowList.ToArray());
        }

        tableTable.Write();
        Console.WriteLine();
    }
}
