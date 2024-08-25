# 配置 Rust 环境

## Install rustup

使用你喜欢的包管理器安装 Rustup。

```sh
# pwsh
sudo winget install --id Rustlang.Rustup
```

然后通过 `rustup` 来管理你的 `rust` 环境。

## 代理

字节的。

```sh
# pwsh
$env:RUSTUP_DIST_SERVER = 'https://rsproxy.cn'
$env:RUSTUP_UPDATE_ROOT = 'https://rsproxy.cn/rustup'
```
