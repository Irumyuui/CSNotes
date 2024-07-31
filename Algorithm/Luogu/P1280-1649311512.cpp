#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector< std::vector<int> > ti(n + 1, std::vector<int>());

    for (int i = 1; i <= m; ++ i) {
        int s, t;
        std::cin >> s >> t;

        ti[s].push_back(t);
    }

    std::vector<int> dp(n + 2, -(1 << 30));
    dp[n + 1] = 0;
    for (int i = n; i >= 1; -- i) {
        if (ti[i].empty())
            dp[i] = dp[i + 1] + 1;
        else
            for (auto t : ti[i]) 
                dp[i] = std::max(dp[i], dp[i + t]);
    }

    std::cout << dp[1] << '\n';

    return 0;
}