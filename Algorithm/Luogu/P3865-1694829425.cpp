#include <bits/stdc++.h>

template <typename Type>
constexpr Type inf = std::numeric_limits<Type>::max() / 2;
using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    std::vector f(std::bit_width<uint>(n), std::vector<int>(n + 1));
    for (int i = 1; i <= n; i ++) {
        f[0][i] = a[i];
    }
    for (int i = 1; i < std::bit_width<uint>(n); i ++) {
        for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
            f[i][j] = std::max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
        }
    }

    auto Ask = [&](int l, int r) {
        int s = std::bit_width<uint>(r - l + 1) - 1;
        return std::max(f[s][l], f[s][r - (1 << s) + 1]);
    };
    
    for (int i = 0; i < q; i ++) {
        int l, r;
        std::cin >> l >> r;
        std::cout << Ask(l, r) << '\n';
    }
}