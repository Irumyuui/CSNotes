#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef unsigned long long ULL;
typedef long double LD;
typedef pair<int, int> PII;

void solve(){
    int x, n;
    cin >> x >> n;
    ULL ans = 1, res = 1;;
    for (int i = 0; i < n; ++ i){
        res *= x;
        ans += res;
        res = ans;
    }
    cout << ans;
    return;
}

int main(){
    FAST();
    // FREIN("in.in");
    solve();
    return 0;
}