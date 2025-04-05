namespace Hakurei;

/// <summary>
/// <A>::=<B>C<D>
/// </summary>
public class Sentence
{
    public Sentence(SyntaxSymbolNode left, in SentenceRightList right)
    {
        Left = left;
        Right = right;
    }

    public Sentence(string sentence)
    {
        var str = sentence.Split("::=");

        if (str.Length is not 2)
            throw new System.Exception($"Unkown sentence: {sentence}");

        var left = str[0];
        var right = str[1];

        if (string.IsNullOrEmpty(left) || left.Length <= 2 || left[0] is not '<' || left[^1] is not '>')
            throw new System.Exception($"Unkown left in: {sentence}");
        // if (string.IsNullOrEmpty(right))
        //     throw new System.Exception($"Unkown right in: {sentence}");

        var leftSym = new SyntaxSymbolNode(left[1..^1]);

        var rightList = new SentenceRightList();
        if (string.IsNullOrEmpty(right))
        {
            rightList.Add(SyntaxSymbolNode.Empty);
        }
        else
        {
            int position = 0;
            while (position < right.Length)
            {
                var current = right[position];
                if (current is '<')
                {
                    var start = position + 1;
                    var end = right.IndexOf('>', position);
                    if (end is not -1)
                    {
                        rightList.Add(new SyntaxSymbolNode(right[start..end]));
                        position = end + 1;
                        continue;
                    }
                }
                rightList.Add(new SyntaxSymbolNode(current.ToString()));
                position++;
            }
        }

        Left = leftSym;
        Right = rightList;
    }

    public SyntaxSymbolNode Left { get; private set; }
    
    public SentenceRightList Right { get; private set; }

    public override string ToString()
        => $"{Left}::={string.Concat(Right)}";

    public static Sentence GetSentence(string sentence) => new Sentence(sentence);

    // public static 
}
