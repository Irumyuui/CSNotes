let inline True x _ = x
let inline False _ y = y
let inline If cond trueExpr falseExpr = cond trueExpr falseExpr

let trueRes = If True 1 2
let falseRes = If False 1 2

printfn "true_res = %d" trueRes
printfn "false_res = %d" falseRes

 