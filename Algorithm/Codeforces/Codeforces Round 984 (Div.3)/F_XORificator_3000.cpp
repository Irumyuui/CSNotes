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
    i64 l, r, i, k;
    std::cin >> l >> r >> i >> k;

    // 0...x
    auto pre_xor_sum = [](i64 x) -> i64 {
        if (auto d = x % 4; d == 0) {
            return x;
        } else if (d == 1) {
            return 1;
        } else if (d == 2) {
            return x + 1;
        } else {
            return 0;
        }
    };

    auto del_pre_sum = [&](i64 x) -> i64 {
        if (x < k)
            return 0;

        // x mod 1 == k mod 1
        if (i == 0) {
            return pre_xor_sum(x);
        }

        i64 cnt = (x - k) / (static_cast<i64>(1) << i) + 1;
        auto ret = pre_xor_sum(cnt - 1) << i;
        if (cnt % 2) {
            ret ^= ((static_cast<i64>(1) << i) - 1) & k;
        }
        return ret;
    };

    auto calc = [&](i64 x) { return pre_xor_sum(x) ^ del_pre_sum(x); };

    std::cout << (calc(r) ^ calc(l - 1)) << '\n';
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