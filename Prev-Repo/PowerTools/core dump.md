# Core Dump

系统调试的重要工具之一是core dump。它是指在程序运行过程中，由于某种原因而被系统强制中断的情况下，生成的内存快照。但是这么重要的工具对于 linux 默认来说是不启用的，需要手动开启。

```sh
$ ulimit --all
Maximum size of core files created                              (kB, -c) 0
Maximum size of a process’s data segment                        (kB, -d) unlimited
Control of maximum nice priority                                    (-e) 0
Maximum size of files created by the shell                      (kB, -f) unlimited
Maximum number of pending signals                                   (-i) 127879
Maximum size that may be locked into memory                     (kB, -l) 65536
Maximum resident set size                                       (kB, -m) unlimited
Maximum number of open file descriptors                             (-n) 1024
Maximum bytes in POSIX message queues                           (kB, -q) 800
Maximum realtime scheduling priority                                (-r) 0
Maximum stack size                                              (kB, -s) 8192
Maximum amount of CPU time in seconds                      (seconds, -t) unlimited
Maximum number of processes available to current user               (-u) 127879
Maximum amount of virtual memory available to each process      (kB, -v) unlimited
Maximum contiguous realtime CPU time                                (-y) unlimited

# 开启 core dump
$ ulimit -c unlimited

$ ulimit --all
Maximum size of core files created                              (kB, -c) unlimited
Maximum size of a process’s data segment                        (kB, -d) unlimited
Control of maximum nice priority                                    (-e) 0
Maximum size of files created by the shell                      (kB, -f) unlimited
Maximum number of pending signals                                   (-i) 127879
Maximum size that may be locked into memory                     (kB, -l) 65536
Maximum resident set size                                       (kB, -m) unlimited
Maximum number of open file descriptors                             (-n) 1024
Maximum bytes in POSIX message queues                           (kB, -q) 800
Maximum realtime scheduling priority                                (-r) 0
Maximum stack size                                              (kB, -s) 8192
Maximum amount of CPU time in seconds                      (seconds, -t) unlimited
Maximum number of processes available to current user               (-u) 127879
Maximum amount of virtual memory available to each process      (kB, -v) unlimited
Maximum contiguous realtime CPU time   
```

这样，如果出现一些异常情况，那么操作系统就会开启 core dump，并将 core 文件保存到当前目录下。我们可以用 `gdb` 工具来分析 core 文件。

## wsl2 没有找到 core dump 文件

```bash
ulimit -c unlimited
sudo bash -c "echo 'core-%t-%E-%p-%s' > /proc/sys/kernel/core_pattern"
```