using Hakurei.CodeAnalyzer;
using System;

namespace Hakurei.CodeAnalyzer;

// Better?
// 
// struct Foo
// {
//     virtual ~Foo() { }
// };
// 
// template<typename TValue>
// struct FooWithValue : public Foo {
//     FooWithValue(TValue value) : Foo(), value(value)
// {
// 
// }
// ~FooWithValue() { }
//     TValue value;
// };
// 
// template < typename TValue >
// bool TryGetValue(const Foo &item, TValue &result) {
//     if (auto target = dynamic_cast<const FooWithValue<TValue>*>(&item); target != nullptr) {
//         result = target->value;
//         return true;
//     }
//     return false;
// }
// 
// int main()
// {
//     FooWithValue<int> foo{ 1};
// 
//     int res1;
//     std::int64_t res2;
//
//     if (TryGetValue(foo, res1)) {
//         std::cout << res1 << '\n';
//     } else {
//         std::cout << "Null\n";
//     }
//     if (TryGetValue(foo, res2)) {
//         std::cout << res1 << '\n';
//     } else {
//         std::cout << "Null\n";
//     }
// }
//

public struct EvaluateResult(object? value, SymbolKind kind, bool defindVariables = false)
{
    public SymbolKind Kind { get; private set; } = kind;

    public bool DefindVariables { get; init;  } = defindVariables;

    // Is better?
    // class Result<T> : BaseResult
    public object? Value { get; private set; } = value;

    public readonly bool Valid => Value is not null;

    public static EvaluateResult VoidResult => new EvaluateResult(null, SymbolKind.Void);

    public static EvaluateResult operator +(EvaluateResult left, EvaluateResult right)
    {
        if (left.Value is int v1) {
            if (right.Value is int v2) {
                return new EvaluateResult(v1 + v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(v1 + f2, SymbolKind.Float);
            }
        }

        if (left.Value is float f1) {
            if (right.Value is int v2) {
                return new EvaluateResult(f1 + v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(f1 + f2, SymbolKind.Float);
            }
        }

        throw new Exception($"Operator '+' cannot be applied to operands of type '{left.Kind}' and '{right.Kind}'");
    }

    public static EvaluateResult operator -(EvaluateResult left, EvaluateResult right)
    {
        if (left.Value is int v1) {
            if (right.Value is int v2) {
                return new EvaluateResult(v1 - v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(v1 - f2, SymbolKind.Float);
            }
        }
        if (left.Value is float f1) {
            if (right.Value is int v2) {
                return new EvaluateResult(f1 - v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(f1 - f2, SymbolKind.Float);
            }
        }

        // throw new Exception($"Unknown type with {left} - {right}");
        throw new Exception($"Operator '-' cannot be applied to operands of type '{left.Kind}' and '{right.Kind}'");
    }

    public static EvaluateResult operator *(EvaluateResult left, EvaluateResult right)
    {
        if (left.Value is int v1) {
            if (right.Value is int v2) {
                return new EvaluateResult(v1 * v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(v1 * f2, SymbolKind.Float);
            }
        }
        if (left.Value is float f1) {
            if (right.Value is int v2) {
                return new EvaluateResult(f1 * v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(f1 * f2, SymbolKind.Float);
            }
        }

        // throw new Exception($"Unknown type with {left} * {right}");
        throw new Exception($"Operator '*' cannot be applied to operands of type '{left.Kind}' and '{right.Kind}'");
    }

    public static EvaluateResult operator /(EvaluateResult left, EvaluateResult right)
    {
        if (left.Value is int v1) {
            if (right.Value is int v2) {
                return new EvaluateResult(v1 / v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(v1 / f2, SymbolKind.Float);
            }
        }
        if (left.Value is float f1) {
            if (right.Value is int v2) {
                return new EvaluateResult(f1 / v2, SymbolKind.Int);
            } else if (right.Value is float f2) {
                return new EvaluateResult(f1 / f2, SymbolKind.Float);
            }
        }

        // throw new Exception($"Unknown type with {left} / {right}");
        throw new Exception($"Operator '/' cannot be applied to operands of type '{left.Kind}' and '{right.Kind}'");
    }

    public override readonly string ToString() => $"{Value ?? "null"}";
}
