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

    std::vector<int> a(n);
    for (auto &x : a) {
        std::cin >> x;
        x--;
    }

    std::vector vis(n, false);
    auto dfs = [&](this auto &self, int from) -> int {
        if (vis[from])
            return 0;
        vis[from] = true;
        return self(a[from]) + 1;
    };

    int ans = 0;
    for (int i = 0; i < n; i++) {
        auto cnt = dfs(i);
        debug(i, cnt);
        ans += (cnt - 1) / 2;
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
