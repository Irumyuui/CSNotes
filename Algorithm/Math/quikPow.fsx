let rec quickPow x b =
    match b with
    | _ when b < 0 -> 0
    | _ when b = 0 -> 1
    | _ when b % 2 = 0 -> quickPow x (b / 2)
    | _ -> x * quickPow (x * x) (b / 2)

let mutQuickPow _a _b =
    let mutable a = _a
    let mutable b = _b
    let mutable res = 1

    while b > 0 do
        if b &&& 1 = 1 then
            res <- res * a

        a <- a * a
        b <- b >>> 1

    res
