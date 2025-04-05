#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 2e3 + 115;
char s1[LEN], s2[LEN];
int dp[LEN][LEN], l1, l2;

void solve(){
    // fill(dp[0], dp[0] + LEN * LEN, 0x7ffffff); 
    cin >> s1 + 1 >> s2 + 1;
    l1 = strlen(s1 + 1);
    l2 = strlen(s2 + 1);
    for (int i = 0; i <= l1; ++ i){
        dp[i][0] = i;
    }
    for (int i = 0; i <= l2; ++ i){
        dp[0][i] = i;
    }
    for (int i = 1; i <= l1; ++ i){
        for (int j = 1; j <= l2; ++ j){
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            if (s1[i] == s2[j]){
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1]);
            }else{
                dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }
    }
    cout << dp[l1][l2] << endn;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}