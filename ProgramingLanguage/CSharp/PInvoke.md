# PInvoke

> 因为之前的工作是需要进行 c# 和 c++ 互操作的，所以这里写一个总结。

很多情况下，C# 的性能可能还是不足以支撑一些场景，比如计算特别多的时候。这时候我们就可以使用 c++ 作为这一部分性能敏感的地方，让 c++ 进行处理，然后上层使用 c# ，这样就可以一石二鸟，既享受 c++ 的高性能，又可以享受 c# 的易用性和生态。

## demangle

这里其实指的是 c++ 在编译时会导致一个问题：编译后的名字就不是原来的名字了。

```c++
void Foo(int x) {
    // ...
}
```

类似于这样的一个函数，在编译之后，就会变成另外一个名字（名字不重要，重要的是需要知道这个名字变了）。如果我们这个函数只是在单独的一个程序集里面的话，那么其实无所谓，毕竟编译前的信息已经足够调用这个函数了。但如果是 c++ 导出一个动态链接库，不管是 dll 还是 so ，那么因为这个命名修饰的问题，我们就不知道这个函数到底是哪一个了。因此，我们需要找一种约定，能够让外部调用到这个函数。

> c++ ABI 也是一个很头疼的问题，所以干脆直接大家都用 c ABI 吧。

```c++
#define EXPORT_METHOD extern "C" __declspec(dllexport)
```

也就是，在 c++ 中，我们需要让这个部分是按照 c 的方式编译和连接的，而后面的 `__declspec(dllexport)` ，是 msvc 的扩展语法，指明这个是作为导出用的。

当然了，除了这个，还需要知道集中调用的约定。

| 约定 | 参数压栈顺序 | 栈清理 |
| :---: | :---: | :---: |
| cdecl | 参数从右到左压栈 | 调用函数负责平栈 |
| stdcall | 参数从右往左压栈 | 被调函数负责平栈 |
| fastcall | 参数从 ECX 和 EDX 寄存器取后，其余从右向左入栈 | 被调函数负责平栈 |
| thiscall | c++ 类函数的调用约定 | |

为什么需要注意调用约定？如果调用一个外部函数的时候，没注意到其本身的调用约定，那么程序栈将被破坏，这是一个很严重的问题，当然解决方法很简单：双方约定好就可以了。

## 基础类型的互操作

比较头疼的是，如果只是导出一个单独的变量的话，是做不了的。不过，导出函数的话还是很好办的。

```c++
extern "C" __declspec(dllexport)
int __stdcall Add(int a, int b) {
    return a + b;
}
```

在 c# 这边，只需要将 dll 的位置指定，并声明一个函数，即可。

```csharp
[DllImport("MyDll.dll", EntryPoint = "Add", CallingConvention = CallingConvention.StdCall)]
static extern int Add(int a, int b);
```

然后在 c# 代码中，直接调用就可以了。

### 字符串

假如需要向 c++ 传入一个不可以变的字符串，要怎么做？因为导出的命名规范是 c 的，因此，接口也必须是使用 c 的方式。

```c++
extern "C" __declspec(dllexport)
void __stdcall DumpString(const char *str) {
    std::cout << std << '\n';
}
```

在 c# 这边，如果只是简单传递一个 string 的话，双方指定好字符串编码后就可以算直接传递 `string` 或者 `StringBuilder` 了，比如下面的例子就是指定传递的字符串编码为 `Ansi` 编码。

```csharp
[DllImport("MyDll.dll", EntryPoint = "DumpString", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
static extern void DumpString(string str);
```

但是这实际上依然还是不明确的，传递的字符串类型还是不明确，因此这边最好的选择方式是**手动指定托管封送的字符串**，即使用 `MarshalAsAttribute` 进行指定。

```csharp
[DllImport("MyDll.dll", EntryPoint = "DumpString", CallingConvention = CallingConvention.StdCall, CharSet = CharSet.Ansi)]
static extern void DumpString([MarshalAs(UnmanagedType.LPStr)] string str);
```

如果是对应结构体当中使用的字符串，那么也需要使用 `MarshalAsAttribute` 进行指定。

```c++
struct Foo {
    char *s1;
    char s2[100];
};
```

```c#
[StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
struct Foo {
    [MarshalAs(UnmanagedType.LPStr)]
    public string s1;

    [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 100)]
    public string s2;
};
```

不过更加一般的是，最好是直接使用 `IntPtr` 进行管理，这样就不会涉及到生命周期的问题。

## P/Invoke 实现机制

在 `windows` 下的实现机制为：

- `LoadLibrary` 加载 dll
- `GetProcAddress` 通过 dll 中的动态链接表中的地址信息，获取指定函数地址

在 `linux` 下的实现则是 ``dlopen`` 和 ``dlsym`` 。


## 一些错误

### 调用约定不一致

调用约定不一致导致的栈破坏。

### 委托异步时，对象生命周期结束

调用 c++ dll 导出函数，委托给 c++ ，c++ 内部又开了一个新的线程时，如果触发 GC，对象生命周期结束，导致委托无法调用。

还有其他的一些引用对象，此时就需要将其 Pin 住，防止 GC 回收。

```csharp
var handle = GCHandle.Alloc(obj, GCHandleType.Pinned);
handle.Free();
```
