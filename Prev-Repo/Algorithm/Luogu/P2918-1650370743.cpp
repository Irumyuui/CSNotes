/**
 * @file P2918 [USACO08NOV]Buying Hay S.cpp
 * @author Cieru
 * @date 2022-04-19
 * 
 */

#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

const int INF = 1 << 29;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, h;
    cin >> n >> h;

    vector<int> p(n), c(n);
    for (int i = 0; i < n; ++ i) {
        cin >> p[i] >> c[i];
    }
    
    vector<int> dp(h + 1 + 5000, 1 << 29);
    dp[0] = 0;
    for (int i = 0; i < n; ++ i) {
        for (int j = p[i]; j <= h + 5000; ++ j) {
            dp[j] = min(dp[j], dp[j - p[i]] + c[i]);
        }
    }

    int ans = INF;
    for (int i = h; i <= h + 5000; ++ i) {
        if (dp[i] != INF) {
            ans = min(ans, dp[i]);
        }
    }

    cout << ans << '\n';
    
    return 0;
}