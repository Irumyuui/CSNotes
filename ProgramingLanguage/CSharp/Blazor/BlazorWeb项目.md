# Blazor Web 项目

## 初始化一个 Blazor Web 项目

从 `net8.0` 开始，Blazor Web 项目模板添加了一个新的 blazor 模板。

```bash
dotnet new blazor --interactivity Auto -o BlazorApp
```

这个模板会创建两个子项目，一个是 `BlazorApp` ，一个是 `BlazorApp.Client` 。`BlazorApp` 就是 `Blazor Server` 项目，会在服务端渲染好之后发送给客户端，而 `Client` 后缀的，就是 `Blazor WebAssembly` 项目，会在浏览器中直接运行。

## Blazor 应用项目结构

```shell
$ exa --tree --level=2
.
├── BlazorApp               // Blazor Server 项目
│  ├── appsettings.json     // 服务器设置
│  ├── Components           // 组件
│  │  ├── App.razor
│  │  ├── Layout            // 格式
│  │  ├── Pages             // 页面
│  │  ├── Routes.razor
│  │  └── Shared            // 共享组件
│  ├── Controllers          // 控制器，用于处理请求
│  ├── Migrations           // 数据库迁移
│  ├── Program.cs
│  ├── Properties           // 启动设置
│  ├── wwwroot
│  └── BlazorApp.csproj
├── BlazorApp.Client        // Blazor WebAssembly 项目
│  ├── Layout               // 格式
│  ├── Pages                // 页面
│  ├── Program.cs           // 启动设置
│  ├── wwwroot
│  └── BlazorApp.Client.csproj
├── BlazorApp.Shared        // 共享项目
│  ├── Data                 // 数据上下文
│  ├── Entities             // 实体
│  ├── Services             // 数据服务端
│  └── BlazorApp.Shared.csproj
└── BlazorApp.sln
```
