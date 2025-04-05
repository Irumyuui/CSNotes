# 抽象数据类型 (Abstract Data Type)

简单来说就是一个包, 这个包里面有一些数据, 然后还带有一些方法 (或者叫函数, 或者叫过程), 然后通过这些方法去改变这些数据, 就像一个状态机一样, 方法就是边.

```csharp
public class Foo {
    // 含有 get 和 set
    public string Name { get; set; } = string.Empty;
}
```
