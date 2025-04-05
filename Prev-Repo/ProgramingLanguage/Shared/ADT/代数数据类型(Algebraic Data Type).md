# 代数数据类型 (Algebraic Data Type)

代数数据类型是一种通过组合得到的数据结构, 函数式编程思想中经常出现该数据类型. 通过组合的来的数据类型有两种类别, "和类型" 与 "积类型".

以一段 f# 代码作为例子:

```fsharp
type Shape =
    | Circle of float
    | Rectangle of float * float
```

对于 `Sharp` 类型来说, 它就是一个和类型, 由 `Circle` 和 `Rectangle` 两个类型组合而成, 且 `Sharp` 类型同一时间内要么是 `Circle`, 要么是 `Rectangle`.

对于 `Circle` 和 `Rectangle` 类型来说, 它们都是积类型, 由一个数据类型和多个数据类型组合而成. `Circle` 类型由 `float` 类型组合而成, 表示圆的半径. `Rectangle` 类型由 `float` 类型和 `float` 类型组合而成, 表示矩形的长和宽.

为什么叫做 "和类型" 与 "积类型"? 考虑类型带来的表达式值结果得所有可能性, 这里以一个简单的类型作为例子:

```fsharp
type Foo = 
    | A of unit
    | B of bool * bool
```

考虑每种类型的可能性, 对于 `Foo` 类型, 要么是 `A` , 要么是 `B` , 且 `A` 类型只有一种可能性, 即 `A ()`, 而 `B` 类型有四种可能性, 即 `B (true, true)`, `B (true, false)`, `B (false, true)`, `B (false, false)`. `Foo` 的所有可能性是来自于 `A` 类型和 `B` 类型的所有可能性之和, 而 `B` 的可能性是乘算的.

不过其实很多情况下, ADT 其实应用挺广泛的:

```fsharp
type Option<'T> =
    | Some of 'T
    | None

type Result<'T, 'E> = 
    | Ok of 'T
    | Error of 'E
```

`Optional` 很多语言作为库中的一部分, 用来判断是否是空值, `Result` 类型用来表示函数执行是否成功, 并返回成功的结果或错误信息.
