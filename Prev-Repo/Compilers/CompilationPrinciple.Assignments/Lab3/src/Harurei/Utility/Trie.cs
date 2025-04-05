using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;

namespace Hakurei.Utility;

internal class Trie
{
    private class TrieNode
    {
        public TrieNode(int count, int depth, SyntaxSymbolNode? sym = null)
        {
            Count = count;
            Depth = depth;
            Sym = sym;
            Children = [];
        }

        public int Count { get; set; }
        public int Depth { get; }
        public SyntaxSymbolNode? Sym { get; set; }

        public SyntaxSymbolNode? Left { get; set; } = null;

        public Dictionary<SyntaxSymbolNode, TrieNode> Children { get; set; }

        public TrieNode? Parent { get; set; } = null;

        public int OutDegrdd => Children.Count;
    }

    private TrieNode Root { get; set; }

    private List<TrieNode> NodeList { get; set; } = [];

    private Trie(SyntaxSymbolNode rootSym)
    {
        Root = new TrieNode(0, 0);
        NodeList.Add(Root);
        Root.Left = rootSym;
    }

    private void Add(SentenceRightList symbolRightList)
    {
        TrieNode now = Root;
        foreach (var symbol in symbolRightList)
        {
            TrieNode? next;
            if (!now.Children.TryGetValue(symbol, out next))
            {
                next = new TrieNode(0, now.Depth + 1, symbol);
                NodeList.Add(next);
                next.Parent = now;
                now.Children.Add(symbol, next);
            }
            now = next;
            now.Count++;
        }
    }

    private Dictionary<SyntaxSymbolNode, List<SentenceRightList>> GetSentences(SyntaxSymbolNode left)
    {
        Queue<TrieNode> queue = [];
        foreach (var node in NodeList)
            if (node.OutDegrdd is 0)
                queue.Enqueue(node);

        int dx = 0;

        while (queue.Count is not 0)
        {
            var now = queue.Dequeue();
            var parent = now.Parent;
            if (parent is null)
                continue;
            if (parent.Depth is not 0 && parent.Count > now.Count && parent.Left is null)
            {
                parent.Left = new SyntaxSymbolNode($"{left.Name}_{dx++}");
            }
            queue.Enqueue(parent);
        }

        Dictionary<SyntaxSymbolNode, List<SentenceRightList>> result = [];
        Queue<(TrieNode, SentenceRightList)> que = [];
        foreach (var node in NodeList)
            if (node.OutDegrdd is 0)
                que.Enqueue((node, []));

        while (que.Count is not 0)
        {
            var (now, list) = que.Dequeue();

            if (now.Sym is not null)
            {
                list.Add(now.Sym!);
            }

            if (now.Left is not null)
            {
                if (!result.TryGetValue(now.Left, out var value))
                {
                    value = [];
                    result.Add(now.Left, value);
                }
                value.Add(new(list.Reverse().ToList()));
                if (now.Depth is > 0)
                {
                    list.Clear();
                    list.Add(now.Left);
                }
            }

            if (--now.Count is 0 && now.Parent is not null)
            {
                que.Enqueue((now.Parent, list));
            }
        }

        return result.Select(item => (item.Key, item.Value.Distinct().ToList()))
                    .ToDictionary();
    }

    public static Dictionary<SyntaxSymbolNode, List<SentenceRightList>> ExtractCommonFactors(SyntaxSymbolNode key, List<SentenceRightList> value)
    {
        var trie = new Trie(key);
        foreach (var sen in value)
            trie.Add(sen);
        return trie.GetSentences(key);
    }
}
