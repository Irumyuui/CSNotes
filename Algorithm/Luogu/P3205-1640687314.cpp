#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INFI = 0x7fffffff;
const LL INFL = 0x7fffffffffffffff;

LL MOD = 19650827;
const int LEN = 1e3 + 5;
LL n, dp[LEN][LEN][2] = {0, }, arr[LEN];

void solve(){
    cin >> n;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
        dp[i][i][0] = 1;
    }
    for (int c = 1; c <= n; ++ c){
        for (int i = 1; i <= n - c; ++ i){
            int j = i + c;
            if (arr[i] < arr[i + 1]){
                dp[i][j][0] += dp[i + 1][j][0];
            }
            if (arr[i] < arr[j]){
                dp[i][j][0] += dp[i + 1][j][1];
            }
            if (arr[j] > arr[i]){
                dp[i][j][1] += dp[i][j - 1][0];
            }
            if (arr[j] > arr[j - 1]){
                dp[i][j][1] += dp[i][j - 1][1];
            }
            dp[i][j][0] %= MOD;
            dp[i][j][1] %= MOD;
        }
    }
    cout << (dp[1][n][0] + dp[1][n][1]) % MOD << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    solve();
    return 0;
}