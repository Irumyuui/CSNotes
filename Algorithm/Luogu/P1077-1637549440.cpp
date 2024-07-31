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

const LL modp = 1e6 + 7;
LL dp[101];
vector<int>flower;

void solve(){
    int n, m;
    cin >> n >> m;
    flower = vector<int>(n + 1);
    for (int i = 1; i <= n; ++ i) cin >> flower[i];
    dp[0] = 1;
    for (int i = 1; i <= n; ++ i){
        for (int j = m; j >= 0; -- j){
            for (int k = 1; k <= min(j, flower[i]); ++ k){
                dp[j] = (dp[j] + dp[j - k]) % modp;
            }
        }
    }
    cout << dp[m] << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}