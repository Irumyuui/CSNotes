#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

LL dp[1001];

void solve(){
    LL t, m;
    cin >> t >> m;
    vector<PLL>goods(m + 1);
    for (int i = 1; i <= m; ++ i){
        cin >> goods[i].first >> goods[i].second;
    }
    for (int i = 1; i <= m; ++ i){
        for (int j = t; j >= goods[i].first; -- j){
            dp[j] = max(dp[j], dp[j - goods[i].first] + goods[i].second);
        }
    }
    cout << dp[t] << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}