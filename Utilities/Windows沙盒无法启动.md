截止 win11 24H2 版本，依然还有这个问题，如果无法启动，那么试着随便找个地方创建 `.wsb` 文件，并在里面写入以下内容，然后通过这个文件启动 windows sandbox。

```xml
<Configuration>
    <vGPU>Disable</vGPU>
    <Networking>Enable</Networking>
</Configuration>
```

原理是将虚拟 GPU 禁用。


