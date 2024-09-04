# Lab: locks

在本次实验中依然是承接上次的实验，继续多线程编程的实践。

## Memory allocator

在该任务中，要为每个 `CPU` 实现单独的内存空闲队列分配，在该分配方式下，若单个 `CPU` 的空闲队列内存不够，则需要从其他 `CPU` 拿走一些空闲内存。

转到 `kernel/kalloc.c` ，我们首先为“每个 `CPU` 的空闲队列”提供基础。

```c
struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
} kmem[NCPU];
```

在添加基础以后，我们要改变原来的构造方式和析构方式。对于构造，我们要为每个锁初始化。对于析构，关机就是析构了，每次启动的时候都会重新初始化，因此不用管。

```c
void
kinit()
{
  for (int i = 0; i < NCPU; i ++) {
    initlock(&kmem[i].lock, "kmem");
    kmem[i].freelist = 0;
  }
  freerange(end, (void*)PHYSTOP);
}
```

我们只是处理了锁的初始化，还没有解决内存的分配问题。一种简单的解决方法是让 `freerange` 直接分配好内存，就像还没改动之前一样，那么我们可以选择直接修改 `kfree` ，让它释放的内存能够回到某个 `CPU` 的空闲队列中，这也是要解决的内存分配与释放问题。

来到 `kfree` ，我们要知道它在哪个 `CPU` 运行，然后把释放的内存交给它就可以了。

```c
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;
  
  push_off();
  int cpu_id = cpuid();
  acquire(&kmem[cpu_id].lock);
  r->next = kmem[cpu_id].freelist;
  kmem[cpu_id].freelist = r;
  release(&kmem[cpu_id].lock);
  pop_off();
}
```

最后就是内存分配 `kalloc` 。我们应当遵循这个逻辑：当前内核线程是在哪个 `CPU` 上运行，那么这个 `CPU` 应当提供内存，如果它不够，那么就需要找其他 `CPU` 中有没有了。这样就结束了内存分配任务。

```c
void *
kalloc(void)
{
  struct run *r;

  push_off();
  int cpu_id = cpuid();
  acquire(&kmem[cpu_id].lock);
  r = kmem[cpu_id].freelist;
  if(r) {
    kmem[cpu_id].freelist = r->next;
  } else {
    for (int i = 0; i < NCPU; i ++) {
      if (i == cpu_id)
        continue;

      acquire(&kmem[i].lock);
      struct run *target = kmem[i].freelist;
      if (target) {
        kmem[i].freelist = target->next;
        r = target;
        release(&kmem[i].lock);
        break;
      }
      release(&kmem[i].lock);
    }
  }
  release(&kmem[cpu_id].lock);
  pop_off();

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
```

最后是统一要注意的点：

- 获取 `cpu_id` ，需要关闭中断才有效，使用它也需要关闭中断，因此这里就需要算好作用域
- 对哪个 `cpu` 进行操作，需要注意为其加锁，否则就会出现竟态
  - `kalloc` 要注意一下什么写法会死锁

## Buffer cache

这个任务中，我们要为 buffer cache 解决一把大锁管理导致性能低下的问题。根据提示，这里可以使用哈希表作为解决目前只能一把大锁管理一个数据结构的问题。我们先将原本的结构改造为哈希表，或者改造为几个桶。那么什么东西作为哈希表的 `key` 呢？这里使用的是 `block_no` ，才能通过测试。

```c
#define BUF_HASH_TABLE_N 13
#define BUF_HASH(BLOCK_NO) (BLOCK_NO % BUF_HASH_TABLE_N)

struct buf_hash_table {
  struct spinlock lock;
  struct buf head;
};

struct {
  // struct spinlock lock;
  struct buf buf[NBUF];
  struct buf_hash_table table[BUF_HASH_TABLE_N];
} bcache;
```

我们依然是解决构造和析构的问题。析构不需要考虑的原因依然是一样的。来到构造，我们需要为每个桶的锁初始化，然后将每个单独的 `buf` 块分配好，最简单的方式就是先分配给一个，不要忘记初始化 `b->lock` 。

```c
void
binit(void)
{
  for (int i = 0; i < BUF_HASH_TABLE_N; i ++) {
    initlock(&bcache.table[i].lock, "bcache");
    bcache.table[i].head.prev = &bcache.table[i].head;
    bcache.table[i].head.next = &bcache.table[i].head;
  }

  for (int i = 0; i < NBUF; i ++) {
    struct buf *b = &bcache.buf[i];

    b->next = bcache.table[0].head.next;    
    b->prev = &bcache.table[0].head;
    b->last_access_tick = 0;
    initsleeplock(&b->lock, "buffer");
    bcache.table[0].head.next->prev = b;
    bcache.table[0].head.next = b;
  }
}
```

注意，上述代码中出现了一个新的字段：`last_access_tick` 。根据实验要求，我们需要实现 `LRU` ，因此需要添加一个字段，以记录其最后访问时间。

```c
struct buf {
  int valid;   // has data been read from disk?
  int disk;    // does disk "own" buf?
  uint dev;
  uint blockno;
  struct sleeplock lock;
  uint refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  uint last_access_tick;
  uchar data[BSIZE];
};
```

对于 `last_access_tick` 要怎样取值，我们可以直接以 `kernel/trap.c` 中的 `ticks` 作为时间戳，只需要一个正确的访问方法即可。

```c
uint get_current_tick() {
  uint result;
  acquire(&tickslock);
  result = ticks;
  release(&tickslock);
  return result;
}
```

对于时间该如何更新，我们应当在对 `buffer` 的访问操作中进行（不包括拿一个和归还）。更新时间操作只需要直接获取一下就可以了。要注意的是，还有一个更改引用计数的行为，此时我们就需要防止其他线程修改它，也就是要为它所在的桶加锁。

```c
// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno)
{
  struct buf *b;

  b = bget(dev, blockno);
  if(!b->valid) {
    virtio_disk_rw(b, 0);
    b->valid = 1;
  }

  b->last_access_tick = get_current_tick();

  return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("bwrite");
  virtio_disk_rw(b, 1);
  b->last_access_tick = get_current_tick();
}

void
bpin(struct buf *b) {
  int table_id = BUF_HASH(b->blockno);

  acquire(&bcache.table[table_id].lock);
  b->refcnt ++;
  release(&bcache.table[table_id].lock);
}

void
bunpin(struct buf *b) {
  int table_id = BUF_HASH(b->blockno);

  acquire(&bcache.table[table_id].lock);
  b->refcnt --;
  release(&bcache.table[table_id].lock);
}
```

我们先转向释放 `buffer` 的操作。在这里，原先的实现是将个块作为链表头部，这样再按照原本的 get 顺序可以实现 `LRU` 功能。不过这里，由于我们是哈希表，而且是使用时间戳作为这个功能，因此在这里只需要直接减少引用计数即可。

```c
// Release a locked buffer.
// Move to the head of the most-recently-used list.
void
brelse(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("brelse");

  releasesleep(&b->lock);

  int table_id = BUF_HASH(b->blockno);
  acquire(&bcache.table[table_id].lock);
  b->refcnt --;
  release(&bcache.table[table_id].lock);
}
```

对于最后的 `bget` ，我们要做的只是以下操作。

1. 查看目标桶中是否已经有了缓存
2. 如果没有，那么当前桶是否有空的块
3. 如果还没有，那么其他位置是否有空的块且访问时间最远古

对于这些操作，我们只需要直接按照上述顺序遍历即可。对于判断缓存是否可用，我们只需查看引用计数是否为 `0` 即可，对于访问时间，我们只需要比较我们自己添加的时间戳即可。

```c
static struct buf*
bget(uint dev, uint blockno)
{
  int table_id = BUF_HASH(blockno);
  
  acquire(&bcache.table[table_id].lock);
  
  // Is the block already cached?
  for (struct buf *b = bcache.table[table_id].head.next; b != &bcache.table[table_id].head; b = b->next) {
    if (b->dev == dev && b->blockno == blockno) {
      b->refcnt ++;
      release(&bcache.table[table_id].lock);
      acquiresleep(&b->lock);
      return b;
    }
  }

  // Not cached.
  // Is the table has a free cache?
  for (struct buf *b = bcache.table[table_id].head.next; b != &bcache.table[table_id].head; b = b->next) {
    if (b->refcnt == 0) {
      b->dev = dev;
      b->blockno = blockno;
      b->valid = 0;
      b->refcnt = 1;
      // b->last_access_tick = get_current_tick();
      release(&bcache.table[table_id].lock);
      acquiresleep(&b->lock);
      return b;
    }
  }

  // Not had free cache.
  // Try move free cache from other table.
  struct buf *free_cache = 0;
  int src_id = -1;
  for (int i = 0; i < BUF_HASH_TABLE_N; i ++) {
    if (i == table_id) 
      continue;
    
    acquire(&bcache.table[i].lock);
    for (struct buf *b = bcache.table[i].head.next; b != &bcache.table[i].head; b = b->next) {
      if (b->refcnt != 0) 
        continue;
      if (free_cache == 0 || free_cache->last_access_tick > b->last_access_tick) {
        free_cache = b;
        src_id = i;
      }
    }
    release(&bcache.table[i].lock);
  }

  if (free_cache) {
    // init
    free_cache->dev = dev;
    free_cache->blockno = blockno;
    free_cache->valid = 0;
    free_cache->refcnt = 1;
    // free_cache->last_access_tick = get_current_tick();

    // take
    acquire(&bcache.table[src_id].lock);
    free_cache->prev->next = free_cache->next;    
    free_cache->next->prev = free_cache->prev;
    release(&bcache.table[src_id].lock);

    // insert
    free_cache->next = bcache.table[table_id].head.next;
    free_cache->prev = &bcache.table[table_id].head;
    bcache.table[table_id].head.next->prev = free_cache;
    bcache.table[table_id].head.next = free_cache;

    release(&bcache.table[table_id].lock);
    acquiresleep(&free_cache->lock);
    return free_cache;
  }

  // Not found.
  panic("bget: no buffers");
}
```