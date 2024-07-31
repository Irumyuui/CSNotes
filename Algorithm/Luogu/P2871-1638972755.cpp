#include <bits/stdc++.h>
using namespace std;

int dp[12885] = {0, };

int main(){
    std::ios::sync_with_stdio(false);
    // freopen("in.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++ i){
        int w, d;
        cin >> w >> d;
        for (int j = m; j >= w; -- j){
            dp[j] = max(dp[j], dp[j - w] + d);
        }
    }
    cout << dp[m];
    return 0;
}