let pipe x fs = fs |> List.fold (fun acc f -> f acc) x


let repeat times f =
    let rec loop n acc =
        if n <= 0 then acc else loop (n - 1) (f acc) in

    loop times


let fib n =
    if n = 1 then
        1
    else
        let transform = fun (a, b) -> b, a + b in pipe (0, 1) [ repeat (n - 1) transform ] |> fun (_, b) -> b


[ 1..10 ] |> List.map fib |> printfn "%A"
