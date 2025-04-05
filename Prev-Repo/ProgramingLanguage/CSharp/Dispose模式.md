# Dispose 模式

处理一些非托管资源的时候需要用。

其实也可以借助这个，来实现 `RAII` 。

```csharp
using (var obj = new Base()) {

}
using (var obj = new Derived()) {

}
using (Base obj = new Derived()) {

}

class Base : IDisposable
{
    // 标记该对象是否已被释放
    private bool _disposed = false;

    // 析构器
    // false 主要是通知不要再处理非托管资源了
    ~Base() => Dispose(false);

    // Dispose 接口
    public void Dispose()
    {
        // 通知释放
        Dispose(true);
        // 标记不再调用终结器
        GC.SuppressFinalize(this);
    }

    // 非密封类最好使用这样的模式
    protected virtual void Dispose(bool disposing)
    {
        if (!_disposed) {
            // 清理非托管资源
            if (disposing) {
                Console.WriteLine("Base disposing.");
            }
            _disposed = true;
        }
    }
}

sealed class Derived : Base
{
    private bool _disposed = false;

    ~Derived() => Dispose(false);

    protected override void Dispose(bool disposing) {
        // 注意这里的范围
        if (!_disposed) {
            if (disposing) {
                Console.WriteLine("Derived disposing.");
            }
            _disposed = true;
        }

        // 调用基类 Dispose 方法
        base.Dispose(disposing);
    }
}
```

注意到，这里可以使用 `using` 语句来实现 `RAII` 。

```csharp
// 资源获取即初始化
using var obj = new Base();

// 离开作用域时即释放资源
```
