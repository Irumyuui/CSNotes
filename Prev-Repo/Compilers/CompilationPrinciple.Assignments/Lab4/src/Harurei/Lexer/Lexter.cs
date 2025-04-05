using System.Collections.Generic;
using Hakurei.CodeAnalyzer;
using Hakurei.CodeAnalyzer.Expression;
using Hakurei.Utility;

namespace Hakurei;

public class Lexter(string[] text)
{
    public string[] Text { get; } = text;

    private int _rol = 0;

    private int _col = 0;

    private (int rol, int col) Position => (_rol, _col);

    //public List<string> Diagostics { get; private set; } = [];

    public char Current
    {
        get {
            if (Position.rol >= Text.Length)
                return '\0';
            if (Position.col >= Text[Position.rol].Length)
                return '\0';
            return Text[Position.rol][Position.col];
        }
    }

    private void Next()
    {
        if (_rol >= Text.Length)
            return;
        _col++;
        if (_col >= Text[_rol].Length) {
            _rol++;
            _col = 0;
        }
    }

    private static System.Text.StringBuilder StringBuilder { get; set; } = new();

    public SyntaxToken NextToken()
    {
        while (SyntaxKindHelper.IsDropChar(Current))
            Next();
        if (SyntaxKindHelper.IsEndOfFile(Current))
            return new SyntaxToken(SyntaxKind.EndOfFile, string.Empty, null, _rol, _col);

        int id = 0;
        if (Automata.NextState(id, Current) is null) {
            var utext = Current.ToString();
            Next();

            Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
                $"Unknown token {utext} in ({_rol}:{_col})"
            );

            var result = new SyntaxToken(SyntaxKind.UnknownToken, utext, null, _rol, _col);
            return result;
        }

        // var start = Position;
        StringBuilder.Clear();
        while (true) {
            var next = Automata.NextState(id, Current);
            if (next is null)
                break;
            StringBuilder.Append(Current);
            Next();
            id = next.Value;

            while (Current is '\r' or '\n') {
                Next();
            }
        }

        var text = StringBuilder.ToString();
        var kind = Automata.GetStateKind(id);

        if (kind is SyntaxKind.IdentifierOrKeyword) {
            if (SyntaxKindHelper.TryGetKeywordKind(text, out var result)) {
                return new SyntaxToken(result, text, null, _rol, _col);
            }
            return new SyntaxToken(SyntaxKind.Identifier, text, null, _rol, _col);
        }

        if (kind is SyntaxKind.ConstantInterger) {
            if (int.TryParse(text, out var result)) {
                return new SyntaxToken(SyntaxKind.ConstantInterger, text, result, _rol, _col);
            } else {
                Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
                    $"Unknown token {text} in ({_rol}:{_col}), except constant interger"
                );
                return new SyntaxToken(SyntaxKind.UnknownToken, text, null, _rol, _col);
            }
        }

        if (kind is SyntaxKind.ConstantFloat) {
            if (float.TryParse(text, out var result)) {
                return new SyntaxToken(SyntaxKind.ConstantFloat, text, result, _rol, _col);
            } else {

                Hakurei.Diagostics.DiagosticHelper.AddDiagostic(
                    $"Unknown token {text} in ({_rol}:{_col}), except constant float"
                );

                return new SyntaxToken(SyntaxKind.UnknownToken, text, null, _rol, _col);
            }
        }

        return new SyntaxToken(kind, text, null, _rol, _col);
    }
}
