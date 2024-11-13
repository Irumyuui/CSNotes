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
    int n;
    std::cin >> n;

    int t = 0;
    for (int i = 1;; i++) {
        if (i & 1) {
            t -= 2 * i - 1;
            if (std::abs(t) > n) {
                std::cout << "Sakurako\n";
                return;
            }
        } else {
            t += 2 * i - 1;
            if (std::abs(t) > n) {
                std::cout << "Kosuke\n";
                return;
            }
        }

        debug(i, t, n);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test_cast = 1;
    std::cin >> test_cast;
    for (int test = 1; test <= test_cast; test++) {
        debug(test);
        Main();
    }
}
