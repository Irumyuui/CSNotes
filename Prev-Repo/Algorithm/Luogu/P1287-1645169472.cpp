#include <bits/stdc++.h>

using ll = long long;

ll f[100][100];

inline void inti() {
    for (int i = 1; i <= 10; ++ i) {
        f[i][1] = 1;
    }
    for (int n = 2; n <= 10; ++ n) {
        for (int m = 1; m <= n; ++ m) {
            f[n][m] = f[n - 1][m - 1] + f[n - 1][m] * m;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    inti();

    int n, m;
    std::cin >> n >> m;

    ll ans = f[n][m];
    for (int i = 2; i <= m; ++ i) {
        ans *= i;
    }

    std::cout << ans;

    return 0;
}