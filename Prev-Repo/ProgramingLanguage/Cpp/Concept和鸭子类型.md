# Concept 和 Duck Typing

如果我要求一个类型，满足一个条件：可以被 `Dump` ，那么这个类长什么样子？

```c++
struct Foo {
    void Dump(this Foo& const self);
};
```

好，那么我们一个简单的例子，我们有个函数，要接收一个具有 `Dump` 方法的对象，怎么做？

```c++
template <typename T>
    requires requires(const T t) { {t.Dump()} -> std::same_as<void>; }
void Foo(const T &obj) {
    obj.Dump();
}
```

有够长的。我们想想，如果对于其他语言，像 `c#` ，更加一般的方式是什么？

```csharp
public interface IDumpable
{
    void Dump();
}

void Foo1(IDumpable obj) => obj.Dump();
void Foo2<T>(T obj) where T : IDumpable => obj.Dump();
```

思考？`Foo1` 和 `Foo2` 有什么区别？一个是确定一个接口类型，一个是……生成具体的代码？？（当然不是全部，如果不是 native aot 下那在运行时也会具体生成代码的，毕竟拿得到类型信息）。

我们又知道，类型信息，只在编译期有效，那么 `concept` 呢？也是在编译期！所以其实如果这个函数编译为一个独立单元的话，那么编译器就没办法再具体生成代码了，此时就失效了。

再具体来讲， `concept` 可以算作为编译期的鸭子类型**约束**。

毕竟其实单纯模板而言，其实也就算是一个鸭子类型了，只要能过编译，那它就是我所要的。

```c++
void Foo(auto obj)
{
    obj.Dump();  // 管他是什么类型呢
}
```

不过为什么 `c++` 不提供类似于接口一样的抽象层呢，虽然这个动态分发的方式依然走的是虚函数。

```rust
pub trait Dump {
    fn dump(&self);
}

pub struct Foo {
    name: String
}
impl Foo {
    pub fn new(name: String) -> Self {
        Self { name }
    }
}
impl Dump for Foo {
    fn dump(&self) {
        println!("Foo: {}", self.name);
    }
}

pub struct Point {
    x: f32,
    y: f32,
}
impl Point {
    fn new(x: f32, y: f32) -> Self {
        Self { x, y }
    }
}
impl Dump for Point {
    fn dump(&self) {
        println!("Point: ({}, {})", self.x, self.y)
    }
}

fn dump(obj: &dyn Dump) {
    obj.dump();
}

fn main() {
    let foo = Foo::new("hello".to_string());
    dump(&foo);

    let point = Point::new(1.1, 2.2);
    dump(&point);
}
```

不过 c++ 可以稍微不那么优雅一点的实现就是了...

```c++
struct IDumpable {
    virtual IDumpable() = default;
    virtual void Dump() = 0;
};
```
