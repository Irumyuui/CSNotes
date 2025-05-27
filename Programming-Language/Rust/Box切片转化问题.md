[Is transmuting &[Box<T>] to &[&T] valid or UB?](https://users.rust-lang.org/t/is-transmuting-box-t-to-t-valid-or-ub/110897)

省流：不一定安全，不保证内存布局一致，安全的转换方法如下。

```rust
fn as_refs<T>(boxes: &[Box<T>]) -> &[&T] {
    let len = boxes.len();
    let ptr = boxes.as_ptr();
    unsafe { std::slice::from_raw_parts(ptr.cast(), len) }
}
```