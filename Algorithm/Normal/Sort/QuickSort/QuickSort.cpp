#include <cstddef>
#include <iostream>
#include <random>
#include <span>
#include <utility>
#include <vector>

std::mt19937_64 rng(std::random_device{}());

template <typename T> size_t quick_sort_parition(std::span<T> arr) {
  std::size_t sorted_index = 0;
  std::size_t pivot_index = rng() % arr.size();

  std::swap(arr[pivot_index], arr.back());
  for (std::size_t i = 0; i + 1 < arr.size(); i++) {
    if (arr[i] < arr.back()) {
      std::swap(arr[i], arr[sorted_index]);
      sorted_index++;
    }
  }
  std::swap(arr.back(), arr[sorted_index]);

  return sorted_index;
}

template <typename T> void quick_sort(std::span<T> arr) {
  if (arr.size() <= 1) {
    return;
  }
  auto pivot = quick_sort_parition(arr);
  quick_sort(arr.first(pivot));
  quick_sort(arr.subspan(pivot + 1));
}

int main() {
  std::cin.tie(nullptr)->sync_with_stdio(false);

  int n;
  std::cin >> n;
  auto a = std::vector<int>(n);
  for (auto &x : a) {
    std::cin >> x;
  }

  quick_sort<int>(a);

  for (auto x : a) {
    std::cout << x << ' ';
  }
}