let rec quickSort (list: 'a list) =
    match list with
    | [] -> []
    | [x] -> [x]
    | x::xs ->
        let smaller = xs |> List.choose(fun y -> if y <= x then Some y else None)
        let larger = xs |> List.choose(fun y -> if y > x then Some y else None)
        quickSort smaller @ [x] @ quickSort larger

let data = [3;2;1;5;4;7;6;9;8]
let result = quickSort data

printfn "%A" result
