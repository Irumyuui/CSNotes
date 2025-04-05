using System;
using System.Diagnostics.Contracts;

namespace Hakurei.CodeAnalyzer;

public static partial class SyntaxKindExtension
{
    public static bool IsType(this SyntaxKind kind) => kind is SyntaxKind.TypeInt or SyntaxKind.TypeFloat
    or SyntaxKind.KeywordInt or SyntaxKind.KeywordFloat;

    public static bool IsIdentifier(this SyntaxKind kind) => kind is SyntaxKind.Identifier;

    public static bool IsConstantNumber(this SyntaxKind kind) => kind is SyntaxKind.ConstantInterger or SyntaxKind.ConstantFloat;
}
