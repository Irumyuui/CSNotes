use std::io::{stdout, BufWriter, Write};

fn main() {
    let mut output = BufWriter::new(stdout());
    let mut it = std::io::stdin().lines();

    let n = it.next().unwrap().unwrap().parse().unwrap();
    let arr = it.next().unwrap().unwrap().split_whitespace().map(|x| x.parse().unwrap()).collect::<Vec<usize>>();

    let mut ans = vec![0; n];
    let mut stk = Vec::with_capacity(n);

    for l in (0..n).rev() {
        while let Some(x) = stk.last() {
            if arr[l] >= arr[*x] {
                stk.pop();
            } else {
                break;
            }
        }

        if let Some(k) = stk.last() {
            ans[l] = *k + 1;
        }
        stk.push(l);
    }

    for x in ans.into_iter() {
        write!(&mut output, "{} ", x).unwrap();
    }
}
