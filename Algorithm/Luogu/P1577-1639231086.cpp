#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

int ll = 0, rr = 0, n, k;
vector<int>rope;

inline bool cancut(int len){
    if (len == 0) return false;
    int cnt = 0;
    for (auto it : rope) cnt += it / len;
    if (cnt >= k) return true;
    return false;
}

void solve(){
    scanf("%d%d", &n, &k);
    rope = vector<int>(n);
    for (auto &it : rope){
        double x;
        scanf("%lf", &x);
        it = int(x * 100);
        rr = max(it, rr);
    }
    while (ll <= rr){
        int mid = ll + ((rr - ll) >> 1);
        if (cancut(mid)) ll = mid + 1;
        else rr = mid - 1;
    }
    printf("%.2lf", (ll - 1) * 1.0 / 100);
}

int main(){
    // FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}