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
    int n, m, q;
    std::cin >> n >> m >> q;

    std::vector a(m, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cin >> a[j][i];
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = 1; j < n; j++) {
            a[i][j] |= a[i][j - 1];
        }
    }

    while (q--) {
        int m;
        std::cin >> m;

        int al = 0, ar = n - 1;
        for (int t = 0; t < m; t++) {
            int r, c;
            char o;
            std::cin >> r >> o >> c;

            r--;
            if (auto &v = a[r]; o == '<') {
                int k = std::ranges::lower_bound(v, c) - v.begin();
                ar = std::min(ar, k - 1);
            } else {
                int k = std::ranges::upper_bound(v, c) - v.begin();
                al = std::max(al, k);
            }
        }

        if (al <= ar) {
            std::cout << al + 1 << '\n';
        } else {
            std::cout << -1 << '\n';
        }
    }
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