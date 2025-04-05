using System;
using System.Linq;

namespace Hakurei.CodeAnalyzer.Text;

// public class SyntaxText {
//     public SyntaxText(string[] text) {
//         Text = text;
//         TotCount = text.Sum(x => x.Length);
//     }

//     private string[] Text { get; }

//     public int TotCount;

//     public char this[Index line, Index pos] => Text[line][pos];

//     private (Index, Index) GetPiarPosition(int position) {
//         Index line = position / Text.Length;
//         Index pos = position % Text[line].Length;
//         return (line, pos);
//     }


//     public char this[int pos] => pos >= TotCount ? '\0' : GetPiarPosition
// }
