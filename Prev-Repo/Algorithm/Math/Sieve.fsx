let rec primes =
    seq {
        yield 2
        let mutable x = 3

        while true do
            if isPrime x then
                yield x

            x <- x + 2
    }

and isPrime x =
    use e = primes.GetEnumerator()

    let rec loop () =
        match e.MoveNext() with
        | true ->
            match e.Current with
            | p when p * p > x -> true
            | p when x % p = 0 -> false
            | _ -> loop ()
        | false -> true

    loop ()

primes |> Seq.take 100 |> Seq.iter (printf "%d ")