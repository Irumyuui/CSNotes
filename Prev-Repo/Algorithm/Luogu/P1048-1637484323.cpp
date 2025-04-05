#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;

LL dp[101][1001];

void solve(){
    LL t, m;
    cin >> t >> m;
    vector<PLL>goods(m + 1);
    for (int i = 1; i <= m; ++ i){
        cin >> goods[i].first >> goods[i].second;
    }
    for (int i = 1; i <= m; ++ i){
        for (int j = t; j >= 0; -- j){
            if (j >= goods[i].first)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - goods[i].first] + goods[i].second);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    cout << dp[m][t] << endl;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}