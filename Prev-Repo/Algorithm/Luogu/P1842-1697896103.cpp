#include <iostream>
#include <limits>
#include <vector>
#include <numeric>
#include <algorithm>

using i64 = int64_t;

template <typename _Ty>
constexpr _Ty inf = std::numeric_limits<_Ty>::max() / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<std::pair<i64,i64>> a(n);
    for (auto &[w, s] : a) {
        std::cin >> w >> s;
    }

    std::ranges::sort(a, [](const auto &a, const auto &b) {
        return a.first + a.second < b.first + b.second;
    });

    i64 pre = 0, ans = -inf<i64>;
    for (auto [w, s] : a) {
        ans = std::max<i64>(ans, pre - s);
        pre += w;
    }
    std::cout << ans << '\n';
}
