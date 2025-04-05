#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)
const int INF = 1 << 28;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    string s;
    cin >> s;

    int n = s.size();
    s = ' ' + s;

    auto check = [&](int l, int r, int len) {
        for (int i = l; i <= r; ++ i) {
            if (s[i] != s[(i - l) % len + l]) {
                return false;
            }
        }
        return true;
    };

    auto choose = [](int len) {
        if (len < 10) {
            return 1;
        } else if (len < 100) {
            return 2;
        } else {
            return 3;
        }
    };

    vector< vector<int> > dp(n + 1, vector<int>(n + 1, INF));
    for (int i = 1; i <= n; ++ i) {
        dp[i][i] = 1;
    }
    for (int c = 1; c < n; ++ c) {
        for (int i = 1, j = i + c; j <= n; ++ i, ++ j) {
            for (int k = i; k < j; ++ k) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            }

            for (int k = i; k < j; ++ k) {
                if ((c + 1) % (k - i + 1) == 0 && check(i, j, k - i + 1)) {
                    dp[i][j] = min(dp[i][j], dp[i][k] + choose((c + 1) / (k - i + 1)) + 2);
                } 
            }
        }
    }
    cout << dp[1][n] << '\n';
    
    return 0;
}