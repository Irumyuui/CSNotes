# Git

## 分支

[分支入门实践](https://learngitbranching.js.org/?locale=zh_CN)

## Config

```sh
# 账号
git config --global user.name "your name"
git config --global user.email "your email"

# 编辑器
git config --global core.editor nvim

# 字符
git config --global core.quotepath false
git config --global gui.encoding utf-8
git config --global i18n.commit.encoding utf-8
git config --global i18n.logoutputencoding utf-8

# 代理
git config --global http.proxy http://127.0.0.1:7890
```

## windows 下文件名过长

```powershell
git config --system core.longpaths true
```
