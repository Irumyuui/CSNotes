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

    std::vector a(n, std::vector<i64>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }

    i64 ans = 0;
    for (int i = 0; i < n; i++) {
        i64 min = inf<i64>;
        for (int x = i, y = 0; x < n && y < n; x++, y++) {
            min = std::min(min, a[x][y]);
        }
        ans += std::abs(std::min<i64>(0, min));
    }
    for (int i = 1; i < n; i++) {
        i64 min = inf<i64>;
        for (int x = 0, y = i; x < n && y < n; x++, y++) {
            min = std::min(min, a[x][y]);
        }
        ans += std::abs(std::min<i64>(0, min));
    }

    std::cout << ans << '\n';
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
