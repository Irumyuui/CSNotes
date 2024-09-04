# RAII

不像 c++ , rust 将析构函数设计一个标志，也就是通过 Drop trait 来实现自动资源管理。（感觉其实这里类似于 c# 的 using 语句会更好点，不过也可以外部控制）

```rust
#[derive(Default)]
struct Foo;

impl Drop for Foo {
    fn drop(&mut self) {
        println!("Dropping Foo");
    }
}

fn main() {
    let _foo = Foo::default();
}
```