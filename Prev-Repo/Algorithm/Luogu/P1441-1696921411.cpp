#include <bits/stdc++.h>

using u32 = uint32_t;
using i64 = int64_t;
using u64 = uint64_t;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> vw(n);
    for (auto &item : vw) {
        std::cin >> item;
    }

    // auto tot = std::accumulate(vw.begin(), vw.end(), 0);
    constexpr int N = 2010;

    int ans = 0;
    for (u32 mask = (1 << (n - m)) - 1; mask < (1 << n); ) {
        std::bitset<N> f{1};
        for (int j = 0; j < n; j += 1) {
            if ((mask >> j) & 1) {
                f |= (f << vw[j]);
            }
        }
        ans = std::max<int>(ans, f.count() - 1);

        auto lb = mask & -mask;
        auto r = mask + lb;
        mask = ((mask ^ r) >> (std::countr_zero(lb) + 2)) | r;
    }

    std::cout << ans << '\n';
}