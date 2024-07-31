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

LL dp[101][101];
const LL modp =1e6 + 7;

void solve(){
    int n, m;
    cin >> n >> m;
    vector<int>flower(n + 1);
    for (int i = 1; i <= n; ++ i) cin >> flower[i];
    dp[0][0] = 1;
    for (int i = 1; i <= n; ++ i){
        for (int j = 0; j <= m; ++ j){
            for (int k = 0; k <= min(flower[i], j); ++ k){
                dp[i][j] = (dp[i][j] + dp[i - 1][j - k]) % modp;
            }
        }
    }
    cout << dp[n][m];
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}