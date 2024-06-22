# 表达式树

```csharp
using System.Linq.Expressions;

// (x, y) => x + y
var x = Expression.Parameter(typeof(int));
var y = Expression.Parameter(typeof(int));
var addResult = Expression.Add(x, y);
var func = Expression.Lambda<Func<int,int,int>>(addResult, x, y);
Console.WriteLine(func.Compile().Invoke(1, 2));
```