let gcd x y =
    let rec gcd x y =
        match y with
        | 0 -> x
        | _ -> gcd y (x % y)

    gcd (abs x) (abs y)


let exgcd a b =
    let rec exgcd a b =
        match b with
        | 0 -> (a, 1, 0)
        | _ -> let (d, x, y) = exgcd b (a % b) in (d, y, x - (a / b) * y)

    exgcd (abs a) (abs b)
