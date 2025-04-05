# Lab: page tables

## 前言

这个实验比较困难（指单纯上机 22 个小时，还不断重复看一遍和调 bug ，以及重新配置环境等等），其中的第一个小实验是带一遍理解 RISC-V 中的 page table ，而第二个小实验则是为每个进程附加一个 kernel page table ，并为第三个小实验提供支持。

## Print a page table

在这个小实验中，我们所需要实现的功能是实现一个 `vmprint` 函数，这个函数可以打印出输入的 page table 的层级结构。

```txt
page table 0x0000000087f6e000
..0: pte 0x0000000021fda801 pa 0x0000000087f6a000
.. ..0: pte 0x0000000021fda401 pa 0x0000000087f69000
.. .. ..0: pte 0x0000000021fdac1f pa 0x0000000087f6b000
.. .. ..1: pte 0x0000000021fda00f pa 0x0000000087f68000
.. .. ..2: pte 0x0000000021fd9c1f pa 0x0000000087f67000
..255: pte 0x0000000021fdb401 pa 0x0000000087f6d000
.. ..511: pte 0x0000000021fdb001 pa 0x0000000087f6c000
.. .. ..510: pte 0x0000000021fdd807 pa 0x0000000087f76000
.. .. ..511: pte 0x0000000020001c0b pa 0x0000000080007000
```

对于这个函数，根据提示可以放在 `kernel/vm.c` 中，同时需要在 `defs.h` 中声明，并在 `exec.c` 中添加指定代码。`vmprint` 看起来像这样。

```c
void vmprint(pagetable_t root_pagetable) {

}
```

由实验手册所提供的输出信息，首先需要输出 page table 的地址，然后是递归输出每个 pte 的信息，因此还需要一个辅助函数实现递归操作，这一部分可以参考 `freewalk` 的写法。

> 判断 pte 是否有效，需要判断 `PTE_V` 这个位上是否为 $1$ 。
> 判断 pte 是否还有子页表，需要判断 `PTE_W` 、`PTE_R` 、`PTE_X` 是否都为 $0$ 。这三位分别代表的是可写、可读、可执行，如果 pte 指向一个子页表，那么这三位都为 $0$ ，否则它就是一个叶子节点。

```c
// kernel/vm.c
void _vmprint(pagetable_t cur_pagetable, int level) {
    if (leve <= 0 || level > 3)
        panic("_vmprint: level range out");

    // 512 == 1 << 9
    // 2^9
    // page table count
    for (int i = 0; i < 512; i ++) {
        pte_t pte = cur_pagetable[i];

        if (pte & PTE_V) {
            printf("..");
            for (int j = 1; j < level; j ++)
                printf(" ..");
            uint64 child = PTE2PA(pte);
            printf("%d: pte %p pa %p", i, pte, child);

            if ((pte & (PTE_W | PTE_R | PTE_X)) == 0)
                _vmprint((pagetable_t)child, level + 1);
        }
    }
}

void vmprint(pagetable_t root_pagetable) {
    printf("page table %p\n", root_pagetable);
    _vmprint(root_pagetable, 1);
}
```

## A kernel page table per process

在这个实验中，我们所需要实现的是：

- 为每个进程切换到内核态的时候都使用自己的内核页表

对于这个操作，我们首先需要为每个进程添加一个内核页表成员。

```c
struct proc {
  ...
  pagetable_t pagetable;       // User page table
  pagetable_t kernel_pagetable;  // a kernel pagetable per process
  ...
};
```

接着就是比较朴素的思考：这个成员应该在哪里初始化？它有什么用（我要怎么利用它）？最后我该如何析构它？

哪一个函数负责初始化一个进程？我们看 `kernel/proc.c` 中的 `allocproc` 函数，它就是负责分配一个进程的。在它其中，可以注意到有这样一个片段：

```c
// An empty user page table.
p->pagetable = proc_pagetable(p);
if(p->pagetable == 0){
    freeproc(p);
    release(&p->lock);
    return 0;
}
```

可以知道，这段代码的作用就是初始化用户页表的。我们的 `kernel_pagetable` 需要在下面进行初始化。通过实验手册可以知道，要为新的进程生成内核页表的合理方式是实现一个类似于 `kvminit` 的修改版本，然后从 `allocproc` 中调用它。以下实现就是由 `kvminit` 修改得到的，内核页表映射完全是照搬实现的。这样实现之后，我们就得到了一个全新的内核页表了。

```c
void uvmmap(pagetable_t upagetable, uint64 va, uint64 pa, uint64 sz, int perm) {
  if (mappages(upagetable, va, sz, pa, perm) != 0)
    panic("uvmmap");
}

pagetable_t proc_kernel_pagetable_init() {
  pagetable_t proc_kernel_pagetable = uvmcreate();
  if (proc_kernel_pagetable == 0) 
    return 0;

  // uart registers
  uvmmap(proc_kernel_pagetable, UART0, UART0, PGSIZE, PTE_R | PTE_W);

  // virtio mmio disk interface
  uvmmap(proc_kernel_pagetable, VIRTIO0, VIRTIO0, PGSIZE, PTE_R | PTE_W);

  // CLINT
  uvmmap(proc_kernel_pagetable, CLINT, CLINT, 0x10000, PTE_R | PTE_W);

  // PLIC
  uvmmap(proc_kernel_pagetable, PLIC, PLIC, 0x400000, PTE_R | PTE_W);

  // map kernel text executable and read-only.
  uvmmap(proc_kernel_pagetable, KERNBASE, KERNBASE, (uint64)etext-KERNBASE, PTE_R | PTE_X);

  // map kernel data and the physical RAM we'll make use of.
  uvmmap(proc_kernel_pagetable, (uint64)etext, (uint64)etext, PHYSTOP-(uint64)etext, PTE_R | PTE_W);

  // map the trampoline for trap entry/exit to
  // the highest virtual address in the kernel.
  uvmmap(proc_kernel_pagetable, TRAMPOLINE, (uint64)trampoline, PGSIZE, PTE_R | PTE_X);

  return proc_kernel_pagetable;
}

static struct proc* allocproc() {
    ...

    p->pagetable = proc_pagetable(p);
    if (p->pagetable == 0) {
        freeproc(p);
        release(&p->lock);
        return 0;
    }

    p->kernel_pagetable = proc_kernel_pagetable_init();
    if (p->kernel_pagetable == 0) {
        freeproc(p);
        release(&p->lock);
        return 0;
    }

    ...
}
```

接着，我们还要按照提示，确保每个进程的内核页表都有该仅存的内核堆栈映射。我们要将 `procinit` 函数中关于内核堆栈的初始化部分转移到 `allocproc` 中。

```c
void
procinit(void)
{
  struct proc *p;
  
  initlock(&pid_lock, "nextpid");
  for(p = proc; p < &proc[NPROC]; p++) {
      initlock(&p->lock, "proc");

      // Move to allocproc
      // 
      // Allocate a page for the process's kernel stack.
      // Map it high in memory, followed by an invalid
      // guard page.
      // char *pa = kalloc();
      // if(pa == 0)
      //   panic("kalloc");
      // uint64 va = KSTACK((int) (p - proc));
      // kvmmap(va, (uint64)pa, PGSIZE, PTE_R | PTE_W);
      // p->kstack = va;
  }
  kvminithart();
}

static struct proc* allocproc() {
    ...

    p->pagetable = proc_pagetable(p);
    if (p->pagetable == 0) {
        freeproc(p);
        release(&p->lock);
        return 0;
    }

    p->kernel_pagetable = proc_kernel_pagetable_init();
    if (p->kernel_pagetable == 0) {
        freeproc(p);
        release(&p->lock);
        return 0;
    }
    // allocate a page for the process's kernel stack.
    char *pa = kalloc();
    if(pa == 0)
        panic("kalloc");
    uint64 va = KSTACK((int) (p - proc));
    uvmmap(p->kernel_pagetable, va, (uint64)pa, PGSIZE, PTE_R | PTE_W);
    p->kstack = va;
    
    ...
}
```

这样，对于内核页表的初始化就结束了。接着我们需要实现的是如何使用 `kernel_pagetable` 。让操作系统使用当前进程的内核页表，我们就需要让操作系统知道要怎么找。

观察 `kvminithart` 函数，第一行是向 `SATP` 寄存器传递一个页表地址，同时将开启 `MMU` ，接着 cpu 所访问的都是虚拟地址，虚拟地址借由 `MMU` 将转换为物理地址。`sfence_vma()` 则是将快表（`TLB`）内容清空，也就是告诉之前的缓存都没用了。

```c
void
kvminithart()
{
    w_satp(MAKE_SATP(kernel_pagetable));
    sfence_vma();
}
````

借由这个函数的启发，我们可以先将所要切换的进程的内核页表先传给 `STAP` ，然后记得清空快表，并在进程跑完后，切换回内核态时重新切换回到全局内核页表。

```c
void
scheduler(void)
{
  struct proc *p;
  struct cpu *c = mycpu();
  
  c->proc = 0;
  for(;;){
    // Avoid deadlock by ensuring that devices can interrupt.
    intr_on();
    
    int found = 0;
    for(p = proc; p < &proc[NPROC]; p++) {
      acquire(&p->lock);
      if(p->state == RUNNABLE) {
        // Switch to chosen process.  It is the process's job
        // to release its lock and then reacquire it
        // before jumping back to us.
        p->state = RUNNING;
        c->proc = p;

        // switch kernel page table from current process.
        w_satp(MAKE_SATP(p->kernel_pagetable));
        sfence_vma();

        swtch(&c->context, &p->context);
        
        // Process is done running for now.
        // It should have changed its p->state before coming back.
        kvminithart();
        c->proc = 0;

        found = 1;
      }
      release(&p->lock);
    }
#if !defined (LAB_FS)
    if(found == 0) {
      intr_on();
      asm volatile("wfi");
    }
#else
    ;
#endif
  }
}
```

最后就是进程的内核页表如何析构的问题了。我们现在要在 `freeproc` 函数中，将进程的内核页表释放。不过，我们这里除了内核页表，还有一个没被释放的东西，即为我们之前所申请的进程内核栈。因此，我们先使用 `uvmunmap` ，解除内核页表和内核栈的映射同时，释放栈空间，然后再释放内核页表，最后再将两个地址清零一下。

```c
static void
freeproc(struct proc *p) {
    ...
     uvmunmap(p->kernel_pagetable, p->kstack, 1, 1);
    freeproc_kernel_pagetable(p->kernel_pagetable);

    // call free proc's kernel pagetable
    p->kernel_pagetable = 0;
    p->kstack = 0;
    ...
}
```

内核页表的释放只需要再一次深度优先遍历一下页表即可，如果有子页表再继续递归释放，同时记得将内存清为 $0$ 。

```c
void freeproc_kernel_pagetable(pagetable_t kernel_pagetable) {
    for (int i = 0; i < 512; i ++) {
        pte_t pte = kernel_pagetable[i];

        // if valib
        if (pte & PTE_V) {
        // if contains
        if ((pte & (PTE_W | PTE_R | PTE_X)) == 0) {
            freeproc_kernel_pagetable((pagetable_t)PTE2PA(pte));
        }
        kernel_pagetable[i] = 0;
        }
    }

    kfree((void *)kernel_pagetable);
}
```

最后，我们还要修改 `kvmpa` 函数内的一个 `walk` 调用参数。因为我们现在已经不是全局的内核页表，因此需要将 `walk` 内的参数更改，否则将喜得 `panic: kvmpa` 的错误。（奇怪的是，在 2021 版本的代码中并没有这一个函数）

```c
uint64 kvmpa(uint64 va)
{
  uint64 off = va % PGSIZE;
  pte_t *pte;
  uint64 pa;
  
  // pte = walk(kernel_pagetable, va, 0);
  pte = walk(myproc()->kernel_pagetable, va, 0);

  if(pte == 0)
    panic("kvmpa");
  if((*pte & PTE_V) == 0)
    panic("kvmpa");
  pa = PTE2PA(*pte);
  return pa+off;
}
```

## Simplify copyin/copyinstr

在这个实验中，我们将利用第二个小实验中所设计的内核页表，实现操作系统直接将虚拟地址替换到物理地址的小操作。在第二个小实验中，我们将 CPU 所目前所要做地址映射的页表加载到了 `SATP` 中，那么也开启了 `MMU` 功能，即现在操作系统访问的地址都是虚拟地址，真正访存的时候将由 `MMU` 在没有感知的情况下把虚拟地址由 `SATP` 中的页表转换为实际的物理地址。

> 为什么 `walk` 明明是模拟 `MMU` 执行虚拟地址转换为物理地址，但是目前的 `xv6` 依然能够正常工作呢？因为 `xv6` 为了简化理解，将内存映射做成了大致等价映射，也就是虚拟地址和物理地址一致。

根据提示，我们需要将 `copyin` 和 `copyinstr` 两个函数替换为其对应的 `new` 版本，并将用户地址的映射添加到每个进程的内核页表，让这两个替换后的函数正常工作。

因为开启了 `MMU` ，我们只需要将用户态中的内存页表让 `MMU` 有个地方能够知道就可以了，那么这个工作自然是交给了 `kernel_pagetable` 了，因为进程能够让 `MMU` 知道的方式只有 `kernel_pagetable` 地址被装载入 `SATP` 的机会。因此，我们这边需要将 `proc->pagetable` 拷贝给 `proc->kernel_pagetable` ，然后这样就能够实现了。

我们可以直接参考 `uvmcopy` ，实现新的复制函数。要注意的是，如果直接使用这边的 `mappages` ，将会发生 `remap` 错误，但是我们这边是直接更新 `kernel_pagetable` ，并不关心其中的内容，因此直接覆写既可，也就是将 `panic` 的地方直接注释掉。还要注意的是，用户地址的 `PTE` 在进程中内核页表中不能具有用户态访问权限，或者说具有用户态访问位的页表不能在内核态中进行访问，因此这边需要记得将 `PTE_U` 移除掉。

```c
int
uvmmappages(pagetable_t pagetable, uint64 va, uint64 size, uint64 pa, int perm)
{
  uint64 a, last;
  pte_t *pte;

  a = PGROUNDDOWN(va);
  last = PGROUNDDOWN(va + size - 1);
  for(;;){
    if((pte = walk(pagetable, a, 1)) == 0)
      return -1;
    // if(*pte & PTE_V)
    //   panic("remap");
    *pte = PA2PTE(pa) | perm | PTE_V;
    if(a == last)
      break;
    a += PGSIZE;
    pa += PGSIZE;
  }
  return 0;
}

// Copy virtual address page table
// Let the kernel use virtual address access memory
// Virtual addresses are converted to physical addresses with the help of MMU
// Instead of using walk() to simulate the conversion in the kernel
//
// The process should copy proc->pagetable to proc->kernel_pagetable when proc->pagetable has changed
// Such as 
//    fork(), exec(), sbrk()
int proc_pagetable_copy(pagetable_t old, pagetable_t new, uint64 begin, uint64 end) {
  begin = PGROUNDUP(begin);

  while (begin < end) {
    // need a src pte
    pte_t* pte_src = walk(old, begin, 0);
    if (pte_src == 0) 
      panic("pagetable_copy: pte should exist");

    if ((*pte_src & PTE_V) == 0)
      panic("pagetable_copy: page not present");

    uint64 pa    = PTE2PA(*pte_src);
    uint   flags = PTE_FLAGS(*pte_src) & (~PTE_U);  // remove PTE_U

    if (uvmmappages(new, begin, PGSIZE, pa, flags) != 0)
      goto err;

    begin += PGSIZE;
  }

  return 0;

 err:
  uvmunmap(new, 0, begin / PGSIZE, 1);
  return -1;
}
```

这边写好以后，我们按照提示的地方，要将几个涉及到用户地址映射修改的函数修改一下，因为这些地方往往也需要对页表的修改，但我们这边进程的内核页表还未对此做出行动，也就是在 `fork` 、`exec` 、`sbrk` 这三个功能中添加对用户地址映射修改行为的响应——将用户页表覆写到其进程的内核页表中。

对于 `fork` ，放在和 `pagetable` 拷贝完以后的位置即可。

```c
// in kernel/proc.c
int fork(void) {
    ...
    // Copy user memory from parent to child.
    if(uvmcopy(p->pagetable, np->pagetable, p->sz) < 0){
        freeproc(np);
        release(&np->lock);
        return -1;
    }
    np->sz = p->sz;

    // Copy user page table to user kernel page table
    if (proc_pagetable_copy(np->pagetable, np->kernel_pagetable, 0, np->sz) < 0) {
        freeproc(np);
        release(&np->lock);
        return -1;
    }
    ...
}
```

对于 `exec` ，直接放在差不多其他地方构造好以后的位置。

```c
// in kernel/exec.c
int exec(char* path, char** argv) {
    ...
    // Commit to the user image.
    oldpagetable = p->pagetable;
    p->pagetable = pagetable;
    p->sz = sz;
    p->trapframe->epc = elf.entry;  // initial program counter = main
    p->trapframe->sp = sp; // initial stack pointer
    proc_freepagetable(oldpagetable, oldsz);

    if (proc_pagetable_copy(p->pagetable, p->kernel_pagetable, 0, sz) < 0)
        goto bad;

    if (p->pid == 1)
        vmprint(p->pagetable);

    return argc; // this ends up in a0, the first argument to main(argc, argv)}
    ...
}
```

对于 `sbrk` 有点特殊，我们需要先看它的代码。

```c
// in kernel/sysproc.c
uint64 sys_sbrk(void) {
    int addr;
    int n;

    if (argint(0, &n) < 0)
        return -1;
    addr = myproc()->sz;
    if(growproc(n) < 0)
        return -1;
    return addr;
}
```

好像没有什么发现？看看 `growproc` ，

```c
int growproc(int n) {
    uint sz;
    struct proc *p = myproc();

    sz = p->sz;
    if(n > 0){
        if((sz = uvmalloc(p->pagetable, sz, sz + n)) == 0) {
            return -1;
        }
    } else if(n < 0){
        sz = uvmdealloc(p->pagetable, sz, sz + n);
    }
    p->sz = sz;
    
    return 0;
}
```

可以发现，这里出现了对用户地址映射修改的位置，因此我们需要进行修改。对于增长的部分，由于有个限制，$sz + n \le PLIC$，因此这边需要判断一下，然后就是要么增长的时候记得也增长，减少的时候，不修改其实也没关系，当那块内存作为脏内存也可以。

```c
int growproc(int n) {
    uint sz;
    struct proc *p = myproc();

    sz = p->sz;
    if(n > 0){
        // Check if memory growth exceeds PLIC
        if (PGROUNDUP(sz + n) > PLIC)
            return -1;

        if((sz = uvmalloc(p->pagetable, sz, sz + n)) == 0) {
            return -1;
        }
        
        if (proc_pagetable_copy(p->pagetable, p->kernel_pagetable, sz - n, sz) < 0)
            return -1;
    } else if(n < 0){
        sz = uvmdealloc(p->pagetable, sz, sz + n);
        if (PGROUNDUP(p->sz) != PGROUNDUP(sz)) {
            uvmunmap(p->kernel_pagetable, PGROUNDUP(sz), (PGROUNDUP(p->sz) - PGROUNDUP(sz)) / PGSIZE, 0);
        }
    }
    p->sz = sz;
    return 0;
}
```

然后是 `userinit` ，这边也需要将刚刚加载好的 `pagetable` 拷贝给 `kernel_pagetable` 。

```c
void userinit(void) {
    ..
    // allocate one user page and copy init's instructions
    // and data into it.
    uvminit(p->pagetable, initcode, sizeof(initcode));
    p->sz = PGSIZE;

    // init kerel page table
    proc_pagetable_copy(p->pagetable, p->kernel_pagetable, 0, p->sz);
        
    ..
}
```

最后，就是直接将 `copyin` 和 `copyinstr` 替换为指定的版本，也就是这两函数作为新函数包装版本即可。

## Grade

除了 `answers-pgtbl.txt` 没写以外。

![](https://img2024.cnblogs.com/blog/2493120/202401/2493120-20240128005127353-1664512126.png)
