#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e3 + 115;
int n;
int dp[LEN][LEN] = {0, }, arr[LEN] = {0, };

void solve(){
    for (int len = 1; len < n; ++ len){
        for (int i = 1; i <= n - len; ++ i){
            int j = i + len;
            dp[i][j] = 0x7fffffff;
            for (int k = i; k < j; ++ k){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j] + arr[j] - arr[i - 1]);
            }
        }
    }
    cout << dp[1][n] << endn;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n;
    int x;
    for (int i = 1; i <= n; ++ i){
        cin >> x;
        arr[i] = arr[i - 1] + x;
    }
    solve();
    return 0;
}