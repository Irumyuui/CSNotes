#include <bits/stdc++.h>

int n, m;
std::vector< std::pair<int, bool> > c;
int ans = 0;

void dfs(int now, int less) {
    if (less == 0) {
        std::vector<bool> dp(int(2000 + 1), 0);
        dp[0] = 1;
        for (int i = 1; i <= n; ++ i) {
            if (c[i].second) {
                continue;
            }
            for (int j = 2000; j >= c[i].first; -- j) {
                dp[j] = dp[j - c[i].first] | dp[j];
            }
        }
        ans = std::max<int>(ans, dp.size() - std::count(dp.begin(), dp.end(), false) - 1);
        return;
    }
    if (now > n) {
        return;
    }
    for (int i = now + 1; i <= n; ++ i) {
        c[i].second = true;
        dfs(i, less - 1);
        c[i].second = false;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n >> m;
    c.assign(n + 1, {0, false});
    for (int i = 1; i <= n; ++ i) {
        std::cin >> c[i].first;
    }
    dfs(0, m);
    std::cout << ans << '\n';

    return 0;
}