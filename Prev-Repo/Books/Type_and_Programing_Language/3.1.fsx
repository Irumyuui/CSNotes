type Data =
    | True
    | False
    | Integer of int

let iszero x =
    match x with
    | Integer x when x = 0 -> True
    | _ -> False

let succ x =
    match x with
    | Integer x -> Integer(x + 1)
    | True -> False
    | False -> True

let pred x =
    match x with
    | Integer x -> Integer(x - 1)
    | True -> False
    | False -> True

let ``if`` cond x y =
    match cond with
    | True -> x
    | False -> y
    | _ -> failwith "Invalid condition"

iszero << pred << succ <| Integer 0 |> printfn "%A" // true
