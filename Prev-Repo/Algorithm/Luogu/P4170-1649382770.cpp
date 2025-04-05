#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.size();
    s = ' ' + s;

    vector< vector<int> > dp(s.size(), vector<int>(s.size(), 1 << 30));
    for (int i = 1; i < s.size(); ++ i)
        dp[i][i] = 1;
    
    for (int len = 1; len < n; ++ len)
        for (int i = 1, j = len + i; j <= n; ++ i, ++ j) {
            if (s[i] == s[j]) 
                dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]);
            for (int k = i; k < j; ++ k) 
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
        }

    cout << dp[1][n] << '\n';
    
    return 0;
}