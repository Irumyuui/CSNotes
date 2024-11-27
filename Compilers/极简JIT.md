# 极简 JIT

在运行时生成代码，并存储在内存中，执行代码则跳转到该内存地址。

```c++
#include <array>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <ostream>
#include <print>

#include <sys/mman.h>

int main(int argc, char *argv[]) {
  auto code = std::array<unsigned char, 6>{0xb8, 0x00, 0x00, 0x00, 0x00, 0xc3};

  if (argc < 2) {
    std::println(std::cerr, "Usage: {} <size>", argv[0]);
    return 1;
  }

  int num = std::atoi(argv[1]);
  *reinterpret_cast<int *>(&code[1]) = num;

  auto mem = mmap(NULL, sizeof(code), PROT_WRITE | PROT_EXEC,
                  MAP_ANON | MAP_PRIVATE, -1, 0);
  std::memcpy(mem, code.data(), sizeof(code));

  auto func = reinterpret_cast<int (*)()>(mem);
  auto ret = func();
  std::println(std::cout, "Result: {}", ret);
}
```
