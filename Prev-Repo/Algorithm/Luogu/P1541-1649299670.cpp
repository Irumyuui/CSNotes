#include <bits/stdc++.h>

using std::max;
using std::min;

int dp[41][41][41][41], cnt[5];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<int> c(n);
    for (int i = 0; i < n; ++ i)
        std::cin >> c[i];

    for (int i = 0; i < m; ++ i) {
        int x;
        std::cin >> x;
        cnt[x] ++;
    }

    dp[0][0][0][0] = c[0];
    for (int i = 0; i <= cnt[1]; ++ i)
        for (int j = 0; j <= cnt[2]; ++ j)
            for (int k = 0; k <= cnt[3]; ++ k)
                for (int l = 0; l <= cnt[4]; ++ l) {
                    if (i)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i - 1][j][k][l] + c[i * 1 + j * 2 + k * 3 + l * 4]);
                    if (j)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j - 1][k][l] + c[i * 1 + j * 2 + k * 3 + l * 4]);
                    if (k)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k - 1][l] + c[i * 1 + j * 2 + k * 3 + l * 4]);
                    if (l)
                        dp[i][j][k][l] = max(dp[i][j][k][l], dp[i][j][k][l - 1] + c[i * 1 + j * 2 + k * 3 + l * 4]);
                }
    
    std::cout << dp[cnt[1]][cnt[2]][cnt[3]][cnt[4]] << '\n';

    return 0;
}