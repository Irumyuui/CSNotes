# Lab: mmap

在本次实验中，我们要实现的是一个比较简简单的 `mmap` 实现，将文件映射到内存中的某个块，并根据权限设置这块内存的行为，以及为其提供延迟分配策略。

## mmap

对于将文件映射到内存，其实是先规划好一块区域给文件使用，为什么要提供延迟分配，是因为如果需要映射一个文件时，就规划好一块内存，将文件读取后直接载入这块内存中的操作显然是花费巨大的，因此需要延迟分配。

当采取延迟分配的策略时，我们就需要先分配好文件载入内存的内存区域，从进程的虚拟内存中找一块可以开辟的区域，然后这样就好了。当进程需要读取这块内存时，因为我们还未映射到实际内存中，因此其会发生缺页中断。我们需要在其发生缺页中断时将对应文件载入一块实际的物理内存中，并将之前的虚拟地址映射到这块分配的物理内存中，也就是载入进程的页表中，此时，我们就实现好了 `mmap` 的功能了。

在添加好系统调用后，我们先不管两个系统调用，而是先加入支持 `vma` 的数据结构。

```c
// kernel/proc.h
#define VMA_COUNT 16

struct virtual_memory_area {
  int is_used;
  uint64 address;
  int length;
  int prot;
  int flags;
  int fd;
  struct file *file;
  int offset;
};

struct proc {
  ...

  struct virtual_memory_area vmas[VMA_COUNT];
};
```

接着，我们着手初始化一下这个 `vma` 数组，只需要将里面的使用标记记为 `0` 即可。

```c
// kernel/proc.c
static struct proc* allocproc(void) {
  ...
  for (int i = 0; i < VMA_COUNT; i ++) {
    p->vmas[i].is_used = 0;
  }

  return p;
}
```

然后，就是实现 `sys_mmap` 。在这里，我将两个系统调用定义放置在了 `kernel/sysfile.h` 中，这样就可以直接使用 `argfd` 了。

在 `sys_mmap` 中，我们所要做的事情是，从当前的进程中找到一个可用的 `vma` ，然后利用输入的参数将这个 `vma` 初始化。对于输入的参数，如果目标文件的权限和输入参数的权限不一致，那么就意味者错误了。在检查好权限之后，我们需要将 `mmap` 申请的内存大小对齐一下，即为 `len = PGROUNDUP(len)` ，对于 `p->sz` 中在 `sbrk` 扩大时已经是地址对齐页大小了，这里也需要将 `len` 对齐一下。

对于新地址的分配，使用的是之前懒惰分配的方式，也就是直接为 `p->sz` 。

根据提示，我们需要对打开的文件增加引用计数，防止文件被关闭。

```c
// kernel/sysfile.c
uint64 sys_mmap(void) {
  uint64 addr;
  int len;
  int prot;
  int flags;
  int fd;
  struct file *file;
  int offset;

  if (argaddr(0, &addr) < 0
  || argint(1, &len) < 0
  || argint(2, &prot) < 0
  || argint(3, &flags)
  || argfd(4, &fd, &file) < 0
  || argint(5, &offset) < 0) {
    return -1;
  }

  struct proc *p = myproc();
  struct virtual_memory_area *vma = 0;
  for (int i = 0; i < VMA_COUNT; i ++) {
    if (!p->vmas[i].is_used) {
      vma = &p->vmas[i];
      break;
    }
  }
  if (vma == 0) {
    return -1;
  }

  if (!file->readable && (prot & PROT_READ))
    return -1;
  if (!file->writable && (prot & PROT_WRITE) && (flags & MAP_SHARED))
    return -1;

  len = PGROUNDUP(len);
  if (p->sz + len >= MAXVA) 
    return -1;

  vma->is_used = 1;
  vma->address = p->sz;
  vma->length = len;
  vma->prot = prot;
  vma->flags = flags;
  vma->fd = fd;
  vma->file = file;
  vma->offset = offset;
  
  filedup(file);
  p->sz += len;

  return vma->address;
}
```

现在，我们实现了 `sys_mmap` ，此时应当转向中断处理程序，处理一下缺页中断。还记得之前实验所处理的两个缺页中断吗？我们现在就需要处理这两个，当发生缺页中断时，将文件真正载入内存中。

我们所需要做的，就是确定这个缺页中断是否属于 `vma` ，然后将其所读取的 `va` 依然是对齐页面，并分配一页页面给它，并将文件的这一页大小数据载入内存中，确认好 `pte` 的权限后将其建立映射关系，这样就做好了延迟分配了。

```c
// kernel/trap.c
void usertrap(void) {
  ...
  } else if (r_scause() == 13 || r_scause() == 15) {
    if (mmap_alloc_page(p, r_stval()) != 0)
      p->killed = -1;
  } else {
  ...
}

// kernel/proc.c
int mmap_alloc_page(struct proc *p, uint64 va) {
  struct virtual_memory_area *vma = 0;
  for (int i = 0; i < VMA_COUNT; i ++) {
    if (p->vmas[i].is_used
    && p->vmas[i].address <= va && va < p->vmas[i].address + p->vmas[i].length) {
      vma = &p->vmas[i];
      break;
    }
  }
  if (vma == 0) {
    return -1;
  }

  uint64 pa = (uint64)kalloc();
  va = PGROUNDDOWN(va);
  if (pa == 0) {
    return -1;
  }
  memset((void*)pa, 0, PGSIZE);

  ilock(vma->file->ip);
  if (readi(vma->file->ip, 0, pa, va - vma->address + vma->offset, PGSIZE) < 0) {
    iunlock(vma->file->ip);
    kfree((void*)pa);
    return -1;
  }
  iunlock(vma->file->ip);

  int pte_flags = PTE_U;
  if (vma->prot & PROT_READ)
    pte_flags |= PTE_R;
  if (vma->prot & PROT_WRITE)
    pte_flags |= PTE_W;
  if (vma->prot & PROT_EXEC)
    pte_flags |= PTE_X;

  if (mappages(p->pagetable, va, PGSIZE, pa, pte_flags) < 0) {
    kfree((void *)pa);
    return -1;
  }

  return 0;
}
```

接下来是 `sys_munmap` 的实现，在确认是哪一块 `vma` 之后，我们需要将其内存对齐一下，检查是否要写回磁盘，然后解除那一块区域内存的映射，并计算剩下的区域。由于保证只会释放两端的内存，所以可以直接计算。记得，当所有虚拟内存区域都被释放了之后，要将文件关闭，同时释放这一块虚拟内存区域。

```c
uint64 sys_munmap(void) {
  uint64 addr;
  int len;

  if (argaddr(0, &addr) < 0 || argint(1, &len) < 0) {
    return -1;
  }

  struct proc *p = myproc();
  struct virtual_memory_area *vma = 0;
  for (int i = 0; i < VMA_COUNT; i ++) {
    if (p->vmas[i].is_used && p->vmas[i].address <= addr && addr < p->vmas[i].address + p->vmas[i].length) {
      vma = &p->vmas[i];
      break;
    }
  }
  if (vma == 0) {
    return -1;
  }

  addr = PGROUNDDOWN(addr);
  len = PGROUNDUP(len);
  if (vma->flags & MAP_SHARED && filewrite(vma->file, addr, len) < 0) {
    // printf("munmap: wtf on this file");
  }

  uvmunmap(p->pagetable, addr, len / PGSIZE, 1);

  if (addr == vma->address) {
    vma->address += len;
    vma->length -= len;
  } else if (addr + len == vma->address + len) {
    vma->length -= len;
  } else {
    panic("munmap: wtf");
  }

  if (vma->length == 0) {
    fileclose(vma->file);
    vma->is_used = 0;
  }

  return 0;
}
```

你可能会注意到，这里如果还没被使用就解除映射关系的话，那么在之前的实验中 `uvmunmap` 会 `panic` ，这里的解决方案与之前的一致。还有，这里也需要将 `uvmcopy` 处理掉。

剩下的，就是解决 `fork` 和 `exit` 的问题了。对于 `fork` ，则是将 `vma` 数组拷贝一份，但是需要将文件引用计数增加一。对于 `exit` ，在等待子进程结束之后，将所有的 `vma` 中文件关闭，如果存在需要写入的内存，将其写入即可。对于这里写入内存，可以实现为脏位才写入，否则不写入，不过都可以通过测试。

```c
// kernel/proc.c
int fork(void) {
  ...
  // Copy user memory from parent to child.
  if(uvmcopy(p->pagetable, np->pagetable, p->sz) < 0){
    freeproc(np);
    release(&np->lock);
    return -1;
  }

  for (int i = 0; i < VMA_COUNT; i ++) {
    np->vmas[i] = p->vmas[i];
    if (np->vmas[i].is_used) {
      filedup(np->vmas[i].file);
    }
  }
  ...
}

void
exit(int status)
{
  ...
  // Close all open files.
  for(int fd = 0; fd < NOFILE; fd++){
    if(p->ofile[fd]){
      struct file *f = p->ofile[fd];
      fileclose(f);
      p->ofile[fd] = 0;
    }
  }

  for (int i = 0; i < VMA_COUNT; i ++) {
    struct virtual_memory_area *vma = &p->vmas[i];
    if (vma->is_used) {
      if (vma->flags & MAP_SHARED && filewrite(vma->file, vma->address, vma->length) < 0) {
        // printf("exit: wtf on this file");
      }
      fileclose(vma->file);
      uvmunmap(p->pagetable, vma->address, vma->length / PGSIZE, 1);
      vma->is_used = 0;
    }
  }
  ...
}
```

这样，本次实验内容就结束了。
