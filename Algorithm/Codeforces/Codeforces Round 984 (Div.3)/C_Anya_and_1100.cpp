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
    std::string s;
    std::cin >> s;

    if (s.size() <= 3) {
        int q;
        std::cin >> q;
        while (q--) {
            int a, b;
            std::cin >> a >> b;
            std::cout << "NO\n";
        }
        return;
    }

    int n = s.size();
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }

    int cnt = 0;
    for (int i = 3; i < n; i++) {
        if (a[i - 3] == 1 && a[i - 2] == 1 && a[i - 1] == 0 && a[i] == 0) {
            cnt++;
        }
    }

    int q;
    std::cin >> q;
    for (int t = 0; t < q; t++) {
        int p, v;
        std::cin >> p >> v;
        p--;

        int l = std::max(3, p), r = std::min(n, p + 4);
        for (int i = l; i < r; i++) {
            if (a[i - 3] == 1 && a[i - 2] == 1 && a[i - 1] == 0 && a[i] == 0) {
                cnt--;
            }
        }
        a[p] = v;
        for (int i = l; i < r; i++) {
            if (a[i - 3] == 1 && a[i - 2] == 1 && a[i - 1] == 0 && a[i] == 0) {
                cnt++;
            }
        }

        std::cout << (cnt > 0 ? "YES" : "NO") << '\n';
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