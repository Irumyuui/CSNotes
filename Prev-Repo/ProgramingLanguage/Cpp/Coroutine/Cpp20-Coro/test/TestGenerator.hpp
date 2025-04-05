#pragma once

#include <iostream>
#include <vector>

#include "Generator.hpp"

[[maybe_unused]]
static void TestGenerator() {
  auto vec = karus::coro::Generator<int>::from(1, 2, 3, 4)
           .for_each([](auto &x) { x *= 2; })
           .collect<std::vector<int>>();

  std::cout << "vector\n";
  for (auto x : vec) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  std::cout << "where x % 3 != 0\n";
  for (auto x : karus::coro::Generator<int>::from_iter(vec)
                  .where([](const auto &x) { return x % 3; })
                  .collect<std::vector<int>>()
  ) {
    std::cout << x << ' ';
  }
  std::cout << '\n';
}
