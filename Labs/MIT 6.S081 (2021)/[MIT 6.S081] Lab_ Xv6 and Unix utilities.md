# Lab: Xv6 and Unix utilities

## Grade

![](https://img2024.cnblogs.com/blog/2493120/202401/2493120-20240121170854673-610212174.png)

## sleep

`sleep` 格式如下

```shell
sleep 5
```

这边需要使用 `kernal/stat.h` 中的 `sleep` 系统调用，并将参数转化为传入。

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: sleep digit");
        exit(1);
    }

    int is_digit = 1, sec = 0;
    for (const char* s = argv[1]; *s; s ++) {
        if (*s >= '0' && *s <= '9') {
            sec = sec * 10 + *s - '0';
        } else {
            is_digit = 0;
            break;
        }
    }

    if (!is_digit) {
        printf("argv must be int");
        exit(1);
    }

    sleep(sec);
    exit(0);
}
```

## pingpong

`pingpong` 需要父进程和子进程之间具有交流信息的能力，也就是使用一对管道。对于父进程，先向子进程传输一个字节的信息，然后等待子进程返回一个字节的信息后 ，输出 `pong` 。对于子进程来说，需要先接收信息，然后输出 `ping` ，再将信息传输回去。要记住的是，及时关闭各个进程的通道读端和写端，也就是及时释放资源。

```c
#include "kernel/types.h"
#include "user/user.h"

int main() {
    const char* msg = "a";
    char buf[2] = {};

    int pipe_p_to_c[2], pipe_c_to_p[2];
    
    // 0:= read fd
    // 1:= write fd
    pipe(pipe_p_to_c);
    pipe(pipe_c_to_p);

    // == 0 := ch p
    if (fork() == 0) {
        close(pipe_p_to_c[0]);
        close(pipe_c_to_p[1]);
        
        read(pipe_p_to_c[0], buf, 1);
        printf("%d: received ping\n", getpid());   
        write(pipe_c_to_p[1], msg, 1);
        
        close(pipe_p_to_c[1]);
        close(pipe_c_to_p[0]);
    } else {
        close(pipe_c_to_p[0]);
        close(pipe_p_to_c[1]);

        write(pipe_p_to_c[1], msg, 1);
        wait(0);
        read(pipe_c_to_p[0], buf, 1);
        printf("%d: received pong\n", getpid());
        
        close(pipe_c_to_p[1]);
        close(pipe_p_to_c[0]);
    }

    exit(0);
}
```

## primes

这一步就比较困难。

首先 `primes` 的要求是：在每个进程中输出还未筛出的第一个素数，并在这个进程中进行一轮筛法，将剩下的数使用 `pipe` 传递给下一个进程。

![](https://img2024.cnblogs.com/blog/2493120/202401/2493120-20240121170910494-1539660594.gif)

```c++
std::vector<int> pri;
bool is_not_pri[N];

void GetPrime() {
    is_not_pro[0] = is_not_pri[1] = true;
    for (int i = 2; i < N; i ++) {
		if (is_not_pri[i])
            continue;
        pri.emplace_back(i);
        for (int j = i * 2; j < N; j += i) {
			is_not_pri[j] = true;
        }
    }
}
```

也就是说，每个进程相当于是 continue 之后的步骤。由于数字范围比较小，可以直接将目前得到的素数作为基准，用这个素数筛去其倍数即可。

需要注意的是，在这里特别要留意资源释放的问题。每次开启 `pipe` ，就必须要释放掉所可能不需要的 `fd` 。同时，父进程需要保留到所有子进程结束后才可退出，这时候就需要 `wait()` 了。

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

__attribute__((noreturn))
void dfs(int rd) {
    int n;
    if (read(rd, &n, 4) == 0) {
        exit(0);
    }
    printf("prime %d\n", n);
    
    int p[2];
    pipe(p);
    
    if (fork() == 0) {
        close(p[0]);
        int m;
        while (read(rd, &m, 4)) {
            if (m % n) {
                write(p[1], &m, 4);
            }
        }
        close(rd);
        close(p[1]);
    } else {
        close(p[1]);
        dfs(p[0]);
    }

    wait(0);
    exit(0);
}

int main() {
    int p[2];
    pipe(p);

    for (int i = 2; i <= 35; i ++) {
        write(p[1], &i, 4);
    }
    close(p[1]);
    dfs(p[0]);

    wait(0);
    exit(0);
}
```

## find

这块可以直接参考 `ls` 的实现，观察 `ls` 是如何遍历目录的，`find` 只是多了需要比较名字的步骤。

```c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include <float.h>

char* get_filename(char* path) {
    static char buf[DIRSIZ + 1] = {};
    
    char* p;
    for (p = path + strlen(path); p >= path && *p != '/'; p --);
    p ++;

    if (strlen(p) >= DIRSIZ) {
        return p;
    }
    memmove(buf, p, strlen(p));
    memset(buf + strlen(p), ' ', DIRSIZ - strlen(p));

    return buf;
}

void find(char *path, char *tar) {
    char buf[512];
    int fd;
    struct stat st;
    
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }
    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    switch (st.type) {
        case T_DEVICE:
        case T_FILE:
            if (strcmp(tar, get_filename(path)) == 0) {
                printf("%s\n", path);
            }
            break;

        case T_DIR:
            if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
                printf("find: path too long\n");
                break;
            }
            strcpy(buf, path);
            
            char* p = buf + strlen(buf);
            *p ++ = '/';
            
            struct dirent de;
            while(read(fd, &de, sizeof(de)) == sizeof(de)) {
                if (de.inum == 0) {
                    continue;
                }

                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                if (stat(buf, &st) < 0) {
                    printf("find: cannot stat %s\n", buf);
                    continue;
                }

                char* name = de.name;
                
                if (st.type != T_DIR) {
                    // goto TAR_FILE;
                    if (strcmp(tar, name) == 0) {
                        printf("%s\n", buf);
                    }
                    continue;
                }
                
                if (strcmp(name, ".") && strcmp(name, "..")) {
                    find(buf, tar);
                }
            }

            break;
        default:
            break;
    }

    close(fd);
    return;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(2, "useage: find path/to/dir file_name\n");
    } else {
        find(argv[1], argv[2]);
    }
    exit(0);
}
```

## xargs

`xargs` 真正执行的就是其第一个参数中的命令，只要从标准输入流中读入前面命令的输出，然后将这个输出作为真正执行的命令的参数，调用 `exec` 即可。

```c
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
    char* xargv[MAXARG] = {};
    for (int i = 1; i < argc; i ++)
        xargv[i - 1] = argv[i];

    char buf[512] = {};
    while (gets(buf, 512)) {
        int len = strlen(buf);
        if (len == 0)
            break;
        if (buf[len - 1] == '\n')
            buf[len - 1] = '\0';
        
        xargv[argc - 1] = buf;
        if (fork() == 0) {
            exec(argv[1], xargv);
        } else {
            wait(0);
        }
    }

    exit(0);
}
```
