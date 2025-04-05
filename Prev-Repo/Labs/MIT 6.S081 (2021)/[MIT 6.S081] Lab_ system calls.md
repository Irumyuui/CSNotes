# Lab: system calls

## 前言

这次实验是实现内核中的两个 `syscall` ：`trace` 和 `sysinfo` 。

回顾一下第三节课，用户态的进程想要执行某个系统调用，例如 `exex(init, argv)` ，首先会将 `init` 和 `argv` 的地址分别存放在 `a0` 和 `a1` 寄存器中，然后 `a7` 存放所要调用的系统调用，最后执行 `ecall`。之后要结束系统调用时，将系统调用的返回值传递给 `a7` ，最后再一次执行 `ecall`。这样，一个系统调用就做完了。

> `ecall` 指令用于 CPU 状态的转换。 

## System call tracing

这里所要实现的是 `sys_trace` ，也就是跟踪命令所调用的系统调用。它的指令格式如下：

```shell
trace trace_mask command
```

其中，`trace_mask` 是一个用来控制追踪系统调用类型的掩码。

首先，我们需要在 `Makefile` 为 `UPROGS` 添加 `$U/_trace` 。

```makefile
UPROGS=\
	...
	$U/_trace\
```

观察 `user/trace.c` ，可以发现其中的 `trace` 函数缺失，需要在 `user/user.h` 中补全一个函数声明。

```c
// system calls
...
int trace(int);
```

按照 Lab 提供的信息，我们还需要在 `user/usys.pl` 中为刚刚添加的系统调用 `trace` 添加一个 `entry` 。

```perl
sub entry {
    my $name = shift;
    print ".global $name\n";
    print "${name}:\n";
    print " li a7, SYS_${name}\n";
    print " ecall\n";
    print " ret\n";
}
...
entry("trace");
```

观察上面的汇编代码，我们可以发现，这个 `perl` 文件的作用就是生成一段汇编，其中 `name` 将会替换为 `entry` 中的系统调用名称。

```asm
.global trace
global:
  li a7, SYS_trace
  ecall
  ret
```

还记得某处的 `initcode` 数组吗？它的实际代码如下：

```asm
# exec(init, argv)
.global start
start:
  la a0, init
  la a1, argv
  li a7, SYS_exec
  ecall
  
# for(;;) exit();
exit:
  li a7, SYS_exit
  ecall
  jal exit
  
# char init[] = "/init\0";
inti:
  .string "/init\0"

# char *argv[] = { init, 0 };
.p2align 2
argv:
  .long init
  .long 0
```

我们可以看到，`a7` 寄存器将会承载 `syscall` 的编号。那么我们的 `SYS_trace` 代号在哪里呢？观察 `kernal/syscall.h` ，可以发现所有的 `syscall` 编号借由宏定义在这里。我们只需要在最后加一个就可以了。

```c
...
#define SYS_close  21
#define SYS_trace  22
```

 此时我们需要看一下，通用的 `syscall` 到底是干了什么。观察 `kernal/syscall.c` ，找到 `void syscall()` 函数定义，将会发现它利用之前的编号，在一个函数指针数组中直接查找对应的系统调用。`trace` 也是一个系统调用，因此我们为这个表补全一个 `sys_trace` 。

```c
// in kernal/syscall.c
...
extern uint64 sys_uptime(void);
extern uint64 sys_trace(void);

static uint64 (*syscalls[])(void) = {
...
  [SYS_trace] sys_trace,  
};
```

到此，我们就开始实现 `sys_trace` 了。

通过 Lab 内容，我们观察 `kernal/sysproc.c` ，可以看到这里包含了很多的 `sys_name` 函数定义，还记得我们之前的 `sys_trace` 吗？我们只是指明了它在某个地方实现，但是目前为之依然还是找不到它。因此，我们要在这个文件下添加一个新的系统调用函数 `sys_trace` ，同时它的签名符合刚才的函数指针表。

```c
uint64
sys_trace(void)
{
  // 获取 `trace` 的参数 trace_mask
  int trace_mask;
  if (argint(0, &trace_mask) < 0)
    return -1;
  // ?
  return 0;
}
```

现在获取到了 `trace_mask` ，但是我们要如何知道被执行的系统调用名称呢，难道是为每个系统调用添加吗？

回顾刚刚的一个通用系统调用 `void syscall(void)` ，可以知道的是，它将知道所有的系统调用具体是什么，那么我们直接修改它就可以了。问题是，要如何让它知道我们需要打印信息呢？

对于每一个执行的进程，应该有一个东西在描述它，那么这个东西最适合的就是描述进程的结构体 `struct proc` 了。我们为它添加一个 `trace_mask` 成员，通过它来传递 `trace` 的信息了。

```c
// in kernal/proc.h
struct proc {
  struct spinlock lock;
  
  ...
  char name[16];               // Process name (debugging)

  uint64 trace_mask;
};
```

回到 `sys_trace` 函数，我们添加了这个成员后，就可以通过它来传递参数了。那么该如何传递呢？`=` 吗？假如命令是 `trace a trace b com` ，那么最后一个命令的关系应该为 `a | b` ，因此这里需要实现的是 `|` 。

```c
uint64
sys_trace(void)
{
  // 获取 `trace` 的参数 trace_mask
  int trace_mask;
  if (argint(0, &trace_mask) < 0)
    return -1;
  // 使用 myproc() 获取当前进程的描述块
  myproc()->trace_mask |= trace_mask;
  return 0;
}
```

到此为止，我们依然还未实现输出跟踪信息。回到 `void syscall(void)` 函数中，我们将利用 `trace_mask` 实现。为了方便，这里需要在多添加一个表，用于记录每个系统调用的名称。此外，对于 `trace_mask` ，如果要输出某一个系统调用，其关系应该为 `(trace_mask & (1 << SYS_which)) == 1` 。

```c
static const char* syscalls_name[] = {
[SYS_fork]    "fork",
[SYS_exit]    "exit",
[SYS_wait]    "wait",
[SYS_pipe]    "pipe",
[SYS_read]    "read",
[SYS_kill]    "kill",
[SYS_exec]    "exec",
[SYS_fstat]   "fstat",
[SYS_chdir]   "chdir",
[SYS_dup]     "dup",
[SYS_getpid]  "getpid",
[SYS_sbrk]    "sbrk",
[SYS_sleep]   "sleep",
[SYS_uptime]  "uptime",
[SYS_open]    "open",
[SYS_write]   "write",
[SYS_mknod]   "mknod",
[SYS_unlink]  "unlink",
[SYS_link]    "link",
[SYS_mkdir]   "mkdir",
[SYS_close]   "close",
[SYS_trace]   "trace",
[SYS_sysinfo] "sysinfo",
};

void
syscall(void)
{
  int num;
  struct proc *p = myproc();

  num = p->trapframe->a7;
  if(num > 0 && num < NELEM(syscalls) && syscalls[num]) {
    p->trapframe->a0 = syscalls[num]();  // return value

    // match trace
    if ((1 << num) & p->trace_mask) {
      // pid: syscall syscall_name ret_value
      printf("%d: syscall %s -> %d\n", p->pid, syscalls_name[num], p->trapframe->a0);
    }
  } else {
    printf("%d %s: unknown sys call %d\n",
            p->pid, p->name, num);
    p->trapframe->a0 = -1;
  }
}
```

有一个问题，初始化呢？进程 fork 后又怎么办呢？

观察 `kernal/proc.c` 中，谁负责新建一个进程呢？`allocproc`。谁负责 fork 呢？ `fork` 。

在 `allocproc` 中，我们只需要记得将新建后的进程块为其 `trace_mask` 初始化为 $0$ 即可。

```c
static struct proc*
allocproc(void)
{
  ...
  
  p->trace_mask = 0;

  return p;
}
```

在 `fork` 中，我们应该是新的进程块与其父进程块的 `trace_mask` 一致。

```c
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *p = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // copy trace mask
  np->trace_mask = p->trace_mask;

  ...
  return pid;
}
```

至此，`sys_trace` 实现完毕了。

## Sysinfo

`sysinfo` 的步骤和 `trace` 的基本步骤差不多，不太需要修改哪些结构体之类的，但是它需要添加点函数，一个计算剩余的内存块大小，一个计算分配的进程数量。

计算内存块的大小，需要观察内存的组织形式。在 `kernal/kalloc.c` 可以看到，内存的组织形式是个链表，直接遍历就行了。要注意的是注意上一下锁。

```c
// in kernel/kalloc.c
// Get free memory byte
uint64
free_mem_byte(void) {
  uint64 free_byte = 0;

  acquire(&kmem.lock);
  struct run *p = kmem.freelist;
  while (p) {
    free_byte += PGSIZE;
    p = p->next;
  }
  release(&kmem.lock);

  return free_byte;
}
```

计算分配出去的进程数，就更直接了，直接遍历进程数组，获取对应的信息即可。

```c
// in kernel/proc.c
// Get process count where state is not unused
uint64
free_proc_count(void) {
  uint64 cnt = 0;

  for (struct proc* p = proc; p < &proc[NPROC]; p ++) {
    cnt += p->state != UNUSED;
  }

  return cnt;
}
```

最后就是 `sys_sysinfo` 的实现，我们只需在函数内将上述两个信息获取到后，将这个信息拷贝到用户态中指定的位置，这个方式可以参考其他位置的实现，重点是看 `copyout` 是如何使用的。

```c
// in kernel/sysproc.c
extern uint64 free_mem_byte();
extern uint64 free_proc_count();

uint64
sys_sysinfo(void) {
  uint64 dst;
  if (argaddr(0, &dst) < 0)
    return -1;

  struct sysinfo info = {
    .freemem = free_mem_byte(),
    .nproc = free_proc_count()
  };

  if (copyout(myproc()->pagetable, dst, (char*)&info, sizeof(info)) < 0)
    return -1;

  return 0;
}
```

## Grade

![](https://img2024.cnblogs.com/blog/2493120/202401/2493120-20240122111520550-1733377408.png)
