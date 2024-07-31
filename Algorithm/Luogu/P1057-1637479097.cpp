#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

int dp[31][31];

void solve(){
    dp[0][1] = 1;
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= m; ++ i){
        for (int j = 1; j <= n; ++ j){
            if (j == 1){
                dp[i][j] = dp[i - 1][n] + dp[i - 1][j + 1];
            }else if (j == n){
                dp[i][j] = dp[i - 1][1] + dp[i - 1][j - 1];
            }else{
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j + 1];
            }
        }
    }
    cout << dp[m][1] << endl;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}