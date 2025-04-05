#include <iostream>
#include <syncstream>
#include <thread>

#include "include/ThreadPool.hpp"

auto main() -> int {
  auto pool = karus::ThreadPool(1);

  for (int i = 0; i < 5; i++) {
    pool.AddTask([i] {
      std::osyncstream(std::cout)
          << "Task: " << i << " Thread id: " << std::this_thread::get_id()
          << std::endl;
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(200ms);
    });
  }

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(2000ms);
  std::osyncstream(std::cout)
      << "====================================================" << std::endl;

  // pool.AddThread(16);

  auto result = pool.SubmitTask([](int x) { return x + 1; }, 10);

  std::cout << result.get() << '\n'; 

  pool.Stop(true);
}
