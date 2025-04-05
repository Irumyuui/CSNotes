#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> m >> n;
    map<int, vector<pair<int, int>>>C;
    for (int i = 0; i < n; ++ i) {
        int a, b, c;
        cin >> a >> b >> c;
        C[c].push_back({a, b});
    }
    vector<int>dp(m + 1, 0);
    for (const auto &[id, W] : C) {
        for (int j = m; j >= 0; -- j) {
            for (auto [v, w] : W) {
                if (j >= v) {
                    dp[j] = max(dp[j], dp[j - v] + w);
                }
            }
        }
    }
    cout << dp[m];

    return 0;
}