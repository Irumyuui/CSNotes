using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Data;
using System.Linq;
using System.Threading;

namespace Hakurei;

public class SentenceGraph
{
    // public SentenceGraph() {
    //     // Map = [];
    //     // SymbolList = [];
    // }

    public SentenceGraph(in SyntaxSymbolNode beginSymbol, in IEnumerable<Sentence> sentences)
    {
        BeginSymbol = beginSymbol;

        Dictionary<SyntaxSymbolNode, List<SentenceRightList>> map = [];
        foreach (var sen in sentences)
            if (map.TryGetValue(sen.Left, out var list))
                list.Add(sen.Right);
            else
                map.Add(sen.Left, [sen.Right]);

        // Map = [];
        foreach (var (key, list) in map)
            Map.Add(key, list.Distinct().ToList());
        // SymbolList = Map.Select(item => item.Key)
        //            .Select((item, index) => (item, index))
        //            .ToDictionary(item => item.index, item => item.item);

        // NoterminalSymbolList = Map.Select(item => item.Key).ToList();
        ReloadSymbolList();
    }

    private Dictionary<SyntaxSymbolNode, List<SentenceRightList>> Map { get; set; } = [];

    public List<SyntaxSymbolNode> NoterminalSymbolList { get; private set; } = [];

    public List<SyntaxSymbolNode> TerminalSymbolList { get; private set; } = [];

    public HashSet<SyntaxSymbolNode> TotSymbolSet { get; private set; } = [];

    public Dictionary<SyntaxSymbolNode, SymbolSet> FirstSet { get; private set; } = [];

    public Dictionary<SyntaxSymbolNode, SymbolSet> FollowSet { get; private set; } = [];

    public PredictiveAnalysisTable? Table { get; private set; } = null;

    public int Count => Map.Count;

    public SyntaxSymbolNode BeginSymbol { get; }

    public bool IsNoterminalSymbol(SyntaxSymbolNode symbol) => Map.ContainsKey(symbol);

    public bool IsTerminalSymbol(SyntaxSymbolNode symbol) => !IsNoterminalSymbol(symbol);

    private void ReloadSymbolList()
    {
        NoterminalSymbolList = Map.Select(item => item.Key).ToList();
        TotSymbolSet.Clear();

        foreach (var (left, right) in Map)
        {
            TotSymbolSet.Add(left);
            foreach (var symList in right)
                foreach (var sym in symList)
                    TotSymbolSet.Add(sym);
        }

        TerminalSymbolList.Clear();
        foreach (var sym in TotSymbolSet)
            if (IsTerminalSymbol(sym))
                TerminalSymbolList.Add(sym);
    }

    /// <summary>
    /// 消除间接左递归
    /// </summary>
    public void RemoveIndirectLeftRecursion()
    {
        for (int i = 0; i < Count; i++)
        {
            for (int j = 0; j < i; j++)
            {
                var first = NoterminalSymbolList[i];
                var second = NoterminalSymbolList[j];

                List<SentenceRightList> list = [];
                foreach (var firNext in Map[first])
                    if (firNext[0] == second)
                        foreach (var secNext in Map[second])
                            list.Add([.. secNext, .. firNext[1..]]);

                var cnt = Map[first].Count;
                foreach (var firNext in Map[first])
                    if (firNext.First != second)
                        list.Add(firNext);

                Map[first] = list.DistinctBy(x => x.ToString()).ToList();
            }
        }
    }

    /// <summary>
    /// 消除直接递归
    /// </summary>
    public void RemoveDirectLeftRecursion()
    {
        Dictionary<SyntaxSymbolNode, List<SentenceRightList>> resolveMap = [];

        for (int i = 0; i < Count; i++)
        {
            var left = NoterminalSymbolList[i];
            var right = Map[left];

            if (!right.Any(x => x.First == left))
            {
                resolveMap.Add(left, right);
                continue;
            }

            var renameLeft = new SyntaxSymbolNode(left.Name + "_LeftRecursion");

            List<SentenceRightList> leftRecursionList = [], keepList = [];
            foreach (var list in right)
                if (list.First == left)
                    leftRecursionList.Add(list);
                else
                    keepList.Add(list);

            List<SentenceRightList> prevList = [], nextList = [[new SyntaxSymbolNode(string.Empty)]];
            foreach (var sen in keepList)
                prevList.Add(
                    [.. sen, renameLeft]
                );
            foreach (var sen in leftRecursionList)
                nextList.Add(
                    [.. sen[1..], renameLeft]
                );

            resolveMap.Add(left, prevList);
            resolveMap.Add(renameLeft, nextList);
        }

        Map = resolveMap;
        // NotermibalSymbolList = Map.Select(item => item.Key).ToList();

        ReloadSymbolList();
    }

    private SymbolSet GetTargetSymbolFristSet(SyntaxSymbolNode targetSymbol)
    {
        SymbolSet result;
        if (FirstSet.TryGetValue(targetSymbol, out result!))
            return result;

        if (IsTerminalSymbol(targetSymbol))
        {
            result = [targetSymbol];
            FirstSet.Add(targetSymbol, result);
            return result;
        }

        result = [];
        foreach (var sen in Map[targetSymbol])
        {
            // var nextSet = GetTargetSymbolFristSet(sen.First);
            // result.UnionWith(nextSet);
            bool allEmpty = true;
            foreach (var item in sen)
            {
                var nexSet = GetTargetSymbolFristSet(item);
                result.UnionWith(nexSet.DropEmptySymbol());
                if (!nexSet.Contains(SyntaxSymbolNode.Empty))
                {
                    allEmpty = false;
                    break;
                }
            }

            if (allEmpty)
                result.Add(SyntaxSymbolNode.Empty);
        }

        FirstSet.Add(targetSymbol, result);

        return result;
    }

    public void ExtractCommonFactors()
    {
        Dictionary<SyntaxSymbolNode, List<SentenceRightList>> resolveMap = [];
        foreach (var (key, value) in Map)
        {
            // var trie = new Trie(key);
            // foreach (var sen in value)
            //     trie.Add(sen);
            // var result = trie.GetSentences(key);
            var result = Hakurei.Utility.Trie.ExtractCommonFactors(key, value);

            foreach (var (nosym, list) in result)
                if (!resolveMap.TryAdd(nosym, list))
                    resolveMap[nosym].AddRange(list);
        }

        Map = resolveMap.Select(item => (item.Key, item.Value.Distinct().ToList()))
                        .ToDictionary();

        ReloadSymbolList();
    }

    public void CalculateFirstSet()
    {
        FirstSet = [];
        foreach (var sym in TotSymbolSet)
            GetTargetSymbolFristSet(sym);
    }

    public void CalculateFollowSet()
    {
        FollowSet = [];
        foreach (var nosym in NoterminalSymbolList)
            FollowSet.Add(nosym, []);

        FollowSet[BeginSymbol].Add(new SyntaxSymbolNode("$"));

        int prevCount = 0;

        while (true)
        {
            for (int i = 0; i < Count; i++)
            {
                var left = NoterminalSymbolList[i];
                foreach (var rightList in Map[left])
                {
                    for (int j = 0; j < rightList.Count; j++)
                    {
                        var now = rightList[j];
                        if (IsNoterminalSymbol(now) && j + 1 < rightList.Count)
                            FollowSet[now].UnionWith(FirstSet[rightList[j + 1]].DropEmptySymbol());

                    }
                    for (int j = rightList.Count - 1; j >= 0; j--)
                    {
                        var now = rightList[j];
                        if (IsNoterminalSymbol(now))
                            FollowSet[now].UnionWith(FollowSet[left]);
                        else
                            break;

                        if (!FirstSet[now].Value.Any(item => item == SyntaxSymbolNode.Empty))
                            break;
                    }
                }
            }
            // foreach (var left in NoterminalSymbolList) {
            //     foreach (var rightList in Map[left]) {
            //         for (int j = 1; j < rightList.Count - 1; j ++) {
            //             var now = rightList[j];

            //         }
            //     }
            // }

            int totCount = FollowSet.Sum(item => item.Value.Count);
            if (prevCount != totCount)
                prevCount = totCount;
            else
                break;
        }
    }

    public List<Sentence> GetSentences()
    {
        List<Sentence> result = [];
        foreach (var (left, list) in Map)
            foreach (var right in list)
                result.Add(new Sentence(left, right));
        return result;
    }

    public bool MatchLL1()
    {
        foreach (var noterminalSymbol in NoterminalSymbolList)
        {
            var exprList = Map[noterminalSymbol];
            for (int i = 1; i < exprList.Count; i++)
            {
                for (int j = 0; j < i; j++)
                {
                    var iFirst = FirstSet[exprList[i].First];
                    var jFirst = FirstSet[exprList[j].First];
                    var aFollow = FollowSet[noterminalSymbol];

                    if (iFirst.HasIntersection(jFirst)
                    || (iFirst.Contains(SyntaxSymbolNode.Empty) && aFollow.HasIntersection(jFirst))
                    || (jFirst.Contains(SyntaxSymbolNode.Empty) && aFollow.HasIntersection(iFirst))
                    )
                    {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    public void CalculateTable()
    {
        Table = new PredictiveAnalysisTable(this);
        Table.CalculateTable();
    }

    public void PrettyPrintSentences()
    {
        foreach (var (left, right) in Map)
        {
            var prev = $"{left} ::= ";
            var idx = prev.IndexOf('=');
            var space = string.Concat(Enumerable.Repeat(' ', prev.Length).Select((c, index) => index == idx ? '|' : c));
            bool first = true;
            foreach (var line in right)
            {
                Console.WriteLine($"{(first ? prev : space)}{line}");
                first = false;
            }
        }
    }

    public void PrettyPrintFirstSet()
    {
        // foreach (var (symbol, symbolSet) in FirstSet)
        //     Console.WriteLine($"FIRST({symbol})={{{string.Join(',', symbolSet)}}}");
        SymbolSet.PrettyPrint("First", FirstSet);
    }

    public void PrettyPrintFollowSet()
    {
        // foreach (var (symbol, symbolSet) in FollowSet)
        //     Console.WriteLine($"FOLLOW({symbol})={{{string.Join(',', symbolSet)}}}");
        SymbolSet.PrettyPrint("Follow", FollowSet);
    }

    public void PrettyPrintTable()
    {
        if (Table is null)
            throw new Exception("Table is not init.");
        Table.PrettyPrint();
    }
}
