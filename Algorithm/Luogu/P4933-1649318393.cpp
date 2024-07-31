#include <bits/stdc++.h>

using ll = long long;
constexpr ll MOD = 998244353;
const int MAXN = 2e4;

ll dp[1010][MAXN * 2 + 10];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++ i)
        std::cin >> v[i];

    ll ans = n;
    for (int i = 1; i <= n; ++ i) {
        for (int j = i - 1; j >= 1; -- j) {
            dp[i][v[i] - v[j] + MAXN] = (dp[i][v[i] - v[j] + MAXN] + dp[j][v[i] - v[j] + MAXN] + 1) % MOD;
            ans = (ans + dp[j][v[i] - v[j] + MAXN] + 1) % MOD;
        }
    }
    std::cout << ans << '\n';

    return 0;
}