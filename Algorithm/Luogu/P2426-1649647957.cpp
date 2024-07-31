#include <bits/stdc++.h>
using namespace std;

#define int long long

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    cin >> n;

    vector<int> c(n + 1, 0);
    for (int i = 1; i <= n; ++ i)
        cin >> c[i];
    
    vector< vector<int> > dp(n + 1, vector<int> (n + 1, 0));
    for (int i = 1; i <= n; ++ i) {
        dp[i][i] = c[i];
    }
    for (int len = 1; len < n; ++ len) {
        for (int i = 1, j = i + len; j <= n; ++ i, ++ j) {
            dp[i][j] = abs(c[j] - c[i]) * (len + 1);
            for (int k = i; k < j; ++ k) {
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }
        }
    }

    cout << dp[1][n] << '\n';
    
    return 0;
}