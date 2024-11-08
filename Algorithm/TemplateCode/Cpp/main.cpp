#if defined(_MSC_VER)
#define _MSVC_TESTING_NVCC
#include <__msvc_all_public_headers.hpp>
#else
#include <bits/stdc++.h>
#endif

#if !defined(ONLINE_JUDGE) || defined(LOCAL_JUDGE)
#include "debug.hpp"
#else
#define debug(...)

#endif

using i64 = std::int64_t;

template <typename T, typename Comp = std::greater<T>>
using Heap = std::priority_queue<T, std::vector<T>, Comp>;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << n + m << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cast = 1;
    // std::cin >> test_cast;
    for (int test = 1; test <= test_cast; test++) {
        debug(test);
        Main();
    }
}