#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

void solve(){
    LL n; cin >> n;
    vector<LL>v(n + 1, 0);
    for (int i = 1; i <= n; ++ i) cin >> v[i];
    sort(v.begin(), v.end());
    int ll = 0, rr = n;
    LL res = 0;
    while (ll < rr){
        res += (v[ll] - v[rr]) * (v[ll] - v[rr]);
        ll ++;
        res += (v[ll] - v[rr]) * (v[ll] - v[rr]);
        rr --;
    }
    cout << res;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}