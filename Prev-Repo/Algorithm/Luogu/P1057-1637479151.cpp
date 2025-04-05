#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

int n, m;
int dp[31][31];

int whic(int num){
    if (num < 1){
        return n;
    }else if (num > n){
        return 1;
    }else{
        return num;
    }
}

void solve(){
    cin >> n >> m;
    dp[0][1] = 1;
    for (int i = 1; i <= m; ++ i){
        for (int j = 1; j <= n; ++ j){
            dp[i][j] = dp[i - 1][whic(j - 1)] + dp[i - 1][whic(j + 1)];
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