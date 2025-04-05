# NativeAOT

`NativeAOT` 随着 `.NET 8` 的发布而推出正式版。

使用的话，只需要以下命令即可体验。

```bash
dotnet pubulish -r linux-x64 -c Release /p:PublishAot=true /p:SelfContained=true
```

- `/p:PublishAot=true` 指明该项目以 `AOT` 方式发布。
- `/p:SelfContained=true` 指明项目生成文件自包含，也就是不会那么多文件
