#include <bits/stdc++.h>

using ll = long long;

std::vector< std::vector<ll> > dp, root;

void dfs(int l, int r) {
    if (l > r)
        return;
    std::cout << root[l][r] << ' ';
    dfs(l, root[l][r] - 1);
    dfs(root[l][r] + 1, r);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    dp = root = std::vector< std::vector<ll> > (n + 1, std::vector<ll> (n + 1, 0));
    for (int i = 1; i <= n; ++ i) {
        std::cin >> dp[i][i];
        root[i][i] = i;
    }

    for (int len = 1; len < n; ++ len) {
        for (int i = 1, j = i + len; j <= n; ++ i, ++ j) {
            // dp[i][j] = std::max(dp[i + 1][j] + dp[i][i], dp[i][j - 1] + dp[j][j]);
            if (dp[i + 1][j] + dp[i][i] > dp[i][j - 1] + dp[j][j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][i];
                root[i][j] = i;
            } else {
                dp[i][j] = dp[i][j - 1] + dp[j][j];
                root[i][j] = j;
            }

            for (int k = i; k < j; ++ k) {
                // dp[i][j] = std::max(dp[i][k - 1] * dp[k + 1][j] + dp[k][k], dp[i][j]);
                if (dp[i][j] < dp[i][k - 1] * dp[k + 1][j] + dp[k][k]) {
                    dp[i][j] = dp[i][k - 1] * dp[k + 1][j] + dp[k][k];
                    root[i][j] = k;
                }
            }
        }
    }
    std::cout << dp[1][n] << '\n';
    dfs(1, n);

    return 0;
}