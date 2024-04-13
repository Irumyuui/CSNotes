# 设计模式

讲真我其实不太懂设计模式，毕竟有些东西呃，比如访问者模式，感觉很怪。

比如访问者模式，它的一个基本实现其实就是下面的两个接口。

```csharp
interface IVisitor {
    void Visit(IVisitable visitable) {
        visitable.Accept(this);
    }
}

interface IVisitable {
    void Accept(IVisitor visitor) {
        visitor.Visit(this);
    }
}
```

然后呢，`Accept` 就是来操作对象的地方，然后有几个类型，就需要写多少个这样的东西。就像我在实现编译器中所实现的方式：

```csharp
public interface ICodeGenVisitable
{
    LLVMValueRef? Accept(ICodeGenVisitor visitor);
}

public interface ICodeGenVisitor
{
    LLVMValueRef? Visit(ArraySubscriptExprNode node);
    LLVMValueRef? Visit(ASTNode node);
    LLVMValueRef? Visit(BinaryOperatorNode node);
    LLVMValueRef? Visit(CallFunctionNode node);
    LLVMValueRef? Visit(CompoundStatementNode node);
    LLVMValueRef? Visit(DeclarationNode node);
    LLVMValueRef? Visit(ExprNode node);
    LLVMValueRef? Visit(FunctionDeclarationNode node);
    LLVMValueRef? Visit(IfStatementNode node);
    LLVMValueRef? Visit<TValue>(IntegerLiteral<TValue> node);
    LLVMValueRef? Visit(LiteralNode node);
    LLVMValueRef? Visit(ProgramNode node);
    LLVMValueRef? Visit(StatementNode node);
    LLVMValueRef? Visit(VariableDeclarationNode node);
    LLVMValueRef? Visit(ReturnStatementNode node);
    LLVMValueRef? Visit(WhileStatementNode node);
}
```

但很头疼的是，为什么要这么写？如果真需要这样，那么为什么我不写一个能够对于多个类型进行处理的函数呢？比如 `c++` 。

```c++
template <typename T>
void Action(T value) {
    if constexpr (std::is_same_v<T, int>) {

    } else if constexpr ...
}
```

这样的实现，感觉只是因为函数没办法直接传递，只能传递一个对象，那么只能通过一个 `visiter` 对象，将 `visitable` 对象转发到对应的处理函数去。

不过 `c#` 应该是不需要这样的设计模式的吧。
