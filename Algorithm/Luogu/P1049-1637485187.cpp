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

LL dp[20002];

void solve(){
    int v, n;
    cin >> v >> n;
    vector<int>goods(n + 1);
    for (int i = 1; i <= n; ++ i){
        cin >> goods[i];
    }
    for (int i = 1; i <= n; ++ i){
        for (int j = v; j >= goods[i]; -- j){
            dp[j] = max(dp[j], dp[j - goods[i]] + goods[i]);
        }
    }
    cout << v - dp[v] << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}