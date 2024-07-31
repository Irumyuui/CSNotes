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

void solve(){
    LL ansi = 0, ansa = 0, len, n;
    cin >> len >> n;
    for (int i = 0; i < n; ++ i){
        LL x;
        cin >> x;
        if (x > 0 && x <= len){
            ansa = max(ansa, max(len - x + 1, x));
            ansi = max(ansi, min(x, len - x + 1));
        }
    }
    cout << ansi << ' ' << ansa << endl;
}

int main(){
    FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}