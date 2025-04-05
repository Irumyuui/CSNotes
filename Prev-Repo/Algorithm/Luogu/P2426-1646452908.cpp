#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e3 + 10;
int a[MAXN], dp[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n; ++ i){
        cin >> a[i];
        dp[i][1] = a[i];
        ans = max(ans, dp[i][1]);
    }
    for (int c = 2; c <= n; ++ c) {
        for (int i = 1; i + c - 1 <= n; ++ i) {
            dp[i][c] = abs(a[i + c - 1] - a[i]) * c;
            for (int k = 1; k < c; ++ k) {
                dp[i][c] = max(dp[i][c], dp[i][k] + dp[i + k][c - k]);
                ans = max(ans, dp[i][c]);
            }
        }
    }
    cout << ans << '\n';

    return 0;
}