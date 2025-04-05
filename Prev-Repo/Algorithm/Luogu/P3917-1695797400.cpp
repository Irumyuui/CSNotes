#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto &x : a) {
        std::cin >> x;
    }
    std::partial_sum(a.begin(), a.end(), a.begin(), std::bit_xor{});

    constexpr int N = std::bit_width((uint)(1e9));
    i64 ans = 0;
    for (int bit = 0; bit < N; bit ++) {
        std::array<i64,2> cnt{1, 0};
        i64 ret = 0;
        for (int i = 0; i < n; i ++) {
            auto d = a[i] >> bit & 1;
            ret += cnt[d ^ 1] * (1ll << bit);
            cnt[d] ++;
        }
        ans += ret;
    }
    std::cout << ans << '\n';
}