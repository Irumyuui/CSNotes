# Lab: xv6 lazy page allocation

## Eliminate allocation from sbrk()

这一步比较简单，直接在 `sys_sbrk` 中将分配内存改为对内存大小进行修改而不分配内存即可。

```c
uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addf = myproc()->sz;
  myproc()->sz += n;

  return 0;
}
```

## Lazy allocation

在这个任务中，我们要实现的是延迟分配内存。在上一个任务中，我们只是实现了 `sys_sbrk` 的延迟分配，此时依然不能正常运行 `echo hi` ，现在我们要实这个操作。

在上个任务完成后，进程如果要访问扩容的内存时，这块内存还未被分配，理所应当的会造成缺页中断了。关于缺页中断，我们需要检查 `scause` 中的错误类型是什么，也就是 `13` 和 `15` ，一个是加载页面错误，一个是保存页面错误。

我们根据运行后得到的错误信息，看一下 `usertrap` 中关于处理错误的地方，为这个地方添加一个能够处理这两个错误的东西。既然是缺页中断，那么这边就需要处理一下缺页的情况，也就是给它分配页面。

```c
// kernel/vm.c
int lazy_alloc_page(struct proc *p, uint64 vaddr) {
  uint64 va = PGROUNDDOWN(vaddr);
  uint64 pa = (uint64)kalloc();
  if (pa == 0) 
    return -1;
  memset((void *)pa, 0, PGSIZE);
  if (mappages(p->pagetable, va, PGSIZE, pa, PTE_W | PTE_R | PTE_U) != 0) {
    kfree((void *)pa);
    return -1;
  }
  return 0;
}

// kernel/trap.c
void usertrap(void) {
  ...
  } else if (r_scause() == 13 || r_scause() == 15) {
    if (lazy_alloc_page(myproc(), r_stval()) != 0) {
      p->killed = 1;
    }
  } else {
  ...
}
```

此时我们尝试运行一下 `echo hi` ，会发现产生一个 `panic: uvmunmap: not mapped` 我们需要修改一下这里。转到 `kernel/vm.c` 。我们继续看 `uvmunmap` 函数，因为是懒分配的页面，那么这里的 `pte` 并不一定是有效的，因此我们需要直接改为 `continue` ，因为它暂时还未被分配。同时，我们还要注意到，如果采取了懒分配的方式，那么意味着在页表中可能找不到指定的 `pte` ，因为它还未被分配，因此第一个 `panic` 也要改为 `continue` 。

```c
void
uvmunmap(pagetable_t pagetable, uint64 va, uint64 npages, int do_free)
{
  uint64 a;
  pte_t *pte;

  if((va % PGSIZE) != 0)
    panic("uvmunmap: not aligned");

  for(a = va; a < va + npages*PGSIZE; a += PGSIZE){
    if((pte = walk(pagetable, a, 0)) == 0)
      continue;
      // panic("uvmunmap: walk");
    if((*pte & PTE_V) == 0)
      continue;
      // panic("uvmunmap: not mapped");
    if(PTE_FLAGS(*pte) == PTE_V)
      panic("uvmunmap: not a leaf");
    if(do_free){
      uint64 pa = PTE2PA(*pte);
      kfree((void*)pa);
    }
    *pte = 0;
  }
}
```

再次运行 `echo hi` ，此时工作正常。

## Lazytests and Usertests

我们目前只是实现了一个很简单的功能，按照 hint 的提示，我们还需要补充一些功能。

目前我们的 `sbrk` 只是简单的加上了 `n` ，因此我们需要修改一下这里的实现，让它能够根据 `n` 为正还是负，适应两种情况。

对于 `n >= 0` ，那我们直接加就好。对于 `n < 0` ，我们就需要判断一下这个大小是否会把内存大小减到负数，如果会，那么说明无效，否则就要将减少的内存回收一下。

```c
uint64 sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;

  if (n > 0) {
    myproc()->sz += n;
  } else if (myproc()->sz > (uint64)(-n)) {
    uvmdealloc(myproc()->pagetable, myproc()->sz, myproc()->sz + n);
    myproc()->sz += n;
  } else {
    return - 1;
  }
  
  return addr;
}
```

接着，我们要判断一下缺页的虚拟地址到底发生在哪里。如果这个虚拟地址发生在栈地址，那么说明无效；如果这个虚拟地址超过了分配给这个进程的总内存，那么也是无效。因此，我们要在我们单独添加的 `lazy_alloc_page` 中先预判一下这个情况。此外，如果这个空间已经分配了，我们不需要再次分配一个页面给它，只需要返回一个 `0` ，告诉外部说已经分配好了就行。

```c
int lazy_alloc_page(struct proc *p, uint64 vaddr) {
  // segmentation fault
  if (p->trapframe->sp > vaddr || p->sz <= vaddr)
    return -1;
  // if is already
  if (walkaddr(p->pagetable, vaddr) != 0)
    return 0;
  
  uint64 va = PGROUNDDOWN(vaddr);
  uint64 pa = (uint64)kalloc();

  if (pa == 0)
    return -1;
  memset((void *)pa, 0, PGSIZE);
  if (mappages(p->pagetable, va, PGSIZE, pa, PTE_W | PTE_R | PTE_U) != 0) {
    kfree((void *)pa);
    return -1;
  }

  return 0;
}
```

接着如果试着运行一下，会发现在 `uvmcopy` 中出现 `panic` ，观察源码可以发现，这里也需要更改一下，因为延迟分配的存在，使得这里会造成 `pte` 还没有或无效的情况。

```c
int
uvmcopy(pagetable_t old, pagetable_t new, uint64 sz)
{
  pte_t *pte;
  uint64 pa, i;
  uint flags;
  char *mem;

  for(i = 0; i < sz; i += PGSIZE){
    if((pte = walk(old, i, 0)) == 0)
      // panic("uvmcopy: pte should exist");
      continue;
    if((*pte & PTE_V) == 0)
      // panic("uvmcopy: page not present");
      continue;
    pa = PTE2PA(*pte);
    flags = PTE_FLAGS(*pte);
    if((mem = kalloc()) == 0)
      goto err;
    memmove(mem, (char*)pa, PGSIZE);
    if(mappages(new, i, PGSIZE, (uint64)mem, flags) != 0){
      kfree(mem);
      goto err;
    }
  }
  return 0;

 err:
  uvmunmap(new, 0, i / PGSIZE, 1);
  return -1;
}
```

到目前为止，我们现在的修改只有一个测试点 `sbrkarg` 无法通过，这个问题是系统调用时，所传入的正确地址还未被分配导致的（也就是 hint 第四点）。我们需要检查一下系统调用的参数，看看地址是否未被分配，若未被分配，则尝试为其分配一下。问题是我们要在哪里知道这个参数在哪里得到的？观察一些系统调用获取参数的方式，都是通过 `argint` 或者 `argaddr` 之类的方式得到的，因此我们要在 `argaddr` 分配一下内存即可。

```c
int argaddr(int n, uint64 *ip) {
  uint64 addr = argraw(n);
  if (walkaddr(myproc()->pagetable, addr) == 0 
  && lazy_alloc_page(myproc(), addr) != 0) {
    return -1;
  }
  *ip = addr;
  return 0;
}
```

## Grade

![](https://img2024.cnblogs.com/blog/2493120/202402/2493120-20240204194551326-1194881108.png)
