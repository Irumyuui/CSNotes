# 正确解压 zip 文件

正确解压 zip 压缩包，且编码正常。

```powershell
$ [System.IO.Compression.ZipFile]::ExtractToDirectory("$pwd/test.zip", "$pwd", [System.Text.Encoding]::GetEncoding((Get-Culture).TextInfo.OEMCodePage)
```
