# map 中需要处理错误

利用 `rust` 强大的类型推导能力。

```rust
fn check_is_odd(i: u32) -> Result<u32, u32> {
    if i % 2 != 0 {
        Err(i)
    } else {
        Ok(i)
    }
}

fn main() {
    let res = (0..100)
        .into_iter()
        .map(check_is_odd)
        .collect::<Result<Vec<u32>, u32>>();

    let _ = res
        .inspect(|r| println!("{:?}", r))
        .inspect_err(|e| eprintln!("Error: {}", e));
}
```
