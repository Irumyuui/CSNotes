# F#

F# 是一个基于 .net 生态的函数式编程语言，能够享用 .net 上的生态。

一个看起来很优雅的快速排序代码如下。

```fsharp
let rec quickSort (comp: 'a -> 'a -> bool) (xs: 'a list) =
    match xs with
    | [] -> []
    | [ x ] -> [ x ]
    | x :: xs ->
        let larger, smaller = List.partition (comp x) xs
        quickSort comp smaller @ [ x ] @ quickSort comp larger
```

你可以这么用，也可以用第二种方式。

```fsharp
// 传参
printfn "%A" (quickSort (fun x y -> x < y) [ 5; 3; 8; 1; 9; 2; 7; 4; 6 ])
// 流
printfn "%A" ([ 5; 3; 8; 1; 9; 2; 7; 4; 6 ] |> quickSort (fun x y -> x < y))
// 再流一点
[ 5; 3; 8; 1; 9; 2; 7; 4; 6 ] |> quickSort (fun x y -> x < y) |> printfn "%A"
```
