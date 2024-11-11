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
    int n, k;
    std::cin >> k >> n;

    std::map<i64, i64> mp;
    for (int i = 0; i < n; i++) {
        i64 b, c;
        std::cin >> b >> c;
        mp[b] += c;
    }

    auto vec = mp | std::views::values | std::ranges::to<std::vector>();
    std::ranges::sort(vec);

    i64 ans = 0;
    while (k > 0 && !vec.empty()) {
        ans += vec.back();
        vec.pop_back();
        k--;
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