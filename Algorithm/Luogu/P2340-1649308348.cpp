#include <bits/stdc++.h>

#define ALL(x) std::begin(x), std::end(x)

const int MAXN = 400000;
int dp[MAXN * 2 + 10];
int a[410], b[410];
int n;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;
    for (int i = 1; i <= n; ++ i)
        std::cin >> a[i] >> b[i];

    std::fill(ALL(dp), -(1 << 30));
    dp[MAXN] = 0;
    for (int i = 1; i <= n; ++ i) {
        if (a[i] >= 0) {
            for (int j = MAXN * 2; j >= a[i]; -- j) 
                dp[j] = std::max(dp[j], dp[j - a[i]] + b[i]);
        } else {
            for (int j = 0; j <= MAXN * 2 + a[i]; ++ j)
                dp[j] = std::max(dp[j], dp[j - a[i]] + b[i]);
        }
    }

    int ans = 0;
    for (int i = MAXN; i <= MAXN * 2; ++ i) 
        if (dp[i] > 0)
            ans = std::max(ans, dp[i] + i - MAXN);
    std::cout << ans << '\n';

    return 0;
}