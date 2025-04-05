let nextPermutation (nums: 'a list) =
    // 先找到一个位置 i，使得 nums.[i] < nums.[i + 1]
    let rec findNotDescPos i =
        match i with
        | _ when i <= -1 -> -1
        | _ when nums.[i] >= nums.[i + 1] -> findNotDescPos (i - 1)
        | _ -> i

    match findNotDescPos (List.length nums - 2) with
    | -1 -> List.rev nums
    | i ->
        // 找到 i 右边的，第一个大于 nums.[i] 的位置 j
        let rec findGtIItemPos j =
            match j with
            | _ when j < 0 -> failwith "impssible"
            | _ when nums.[i] >= nums.[j] -> findGtIItemPos (j - 1)
            | _ -> j

        let j = findGtIItemPos (List.length nums - 1)

        // [0..i-1] [j]
        let prev = nums.[.. i - 1] @ [ nums.[j] ]

        // [i+1..j-1] [i] [j+1..] |> rev
        let tail = nums.[i + 1 .. j - 1] @ [ nums.[i] ] @ nums.[j + 1 ..] |> List.rev

        prev @ tail

let mutable nums = [ 1; 2; 3 ]

for i in 1..6 do
    printfn "%A" nums
    nums <- nextPermutation nums
