#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> sum(n + 1, 0);
    for (int i = 1; i <= n; ++ i) {
        int x;
        std::cin >> x;
        if (x == 1) 
            sum[i] = sum[i - 1] + 1;
        else
            sum[i] = sum[i - 1] - 1;
    }

    auto check = [&](int i, int j) {
        auto tmp = std::abs(sum[i] - sum[j]);
        return i - j == tmp || tmp <= m;
    };

    std::vector<int> dp(n + 1, 1 << 30);
    dp[0] = 0;
    for (int i = 1; i <= n; ++ i)
        for (int j = 0; j < i; ++ j) 
            if (check(i, j))
                dp[i] = std::min(dp[i], dp[j] + 1);
    std::cout << dp[n] << '\n';

    return 0;
}