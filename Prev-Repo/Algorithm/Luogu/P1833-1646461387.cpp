#include <bits/stdc++.h>
using namespace std;
struct Node {
    int t, w, cnt;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    char ch;
    int h1, m1, h2, m2;
    cin >> h2 >> ch >> m2;
    cin >> h1 >> ch >> m1;
    int M = (h1 * 60 + m1) - (h2 * 60 + m2);
    int n; cin >> n;
    vector<Node>C(n);
    for (auto &[t, w, cnt] : C) 
        cin >> t >> w >> cnt;
    vector<long long>dp(M + 1, 0);
    for (auto [t, w, cnt] : C) {
        if (cnt) {
            int k = 1;
            while (cnt >= k) {
                cnt -= k;
                for (int j = M; j >= k * t; -- j)
                    dp[j] = max(dp[j], dp[j - k * t] + w * k);
                k <<= 1;
            }
            if (cnt > 0) 
                for (int j = M; j >= cnt * t; -- j) 
                    dp[j] = max(dp[j], dp[j - cnt * t] + cnt * w);
        } else {
            for (int j = t; j <= M; ++ j) 
                dp[j] = max(dp[j], dp[j - t] + w);
        }
    }
    cout << dp[M];
    
    return 0;
}