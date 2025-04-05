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

using u64 = std::uint64_t;

// std::array<u64, 60> fib;

constexpr u64 MOD = 1e9 + 7;

void Main() {
    static std::vector<u64> fib;
    fib.reserve(2e6 + 10);

    fib.clear();

    u64 n, k;
    std::cin >> n >> k;
    n %= MOD;

    if (k == 1) {
        std::cout << n << '\n';
        return;
    }

    // loop...
    fib.emplace_back(1);
    fib.emplace_back(1);

    for (u64 i = 2;; i++) {
        fib.emplace_back((fib[i - 1] + fib[i - 2]) % k);
        if (fib.back() == 0) {
            // debug(i + 1, k);
            // debug((i + 1) % MOD * n % MOD);
            std::cout << (i + 1) % MOD * n % MOD << '\n';
            return;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // fib[0] = fib[1] = 1;
    // for (int i = 2; i < fib.size(); i++) {
    //     fib[i] = fib[i - 1] + fib[i - 2];
    // }

    // debug(fib);

    // for (int i = 1377; i <= 1377; i++) {
    //     debug(i);
    //     int cnt = 0;
    //     for (int j = 0; j < fib.size(); j++) {
    //         if (fib[j] % i == 0) {
    //             debug(j + 1, i);
    //             cnt++;
    //             if (cnt >= 2)
    //                 break;
    //         }
    //     }
    // }

    int test_cast = 1;
    std::cin >> test_cast;
    for (int test = 1; test <= test_cast; test++) {
        debug(test);
        Main();
    }
}
