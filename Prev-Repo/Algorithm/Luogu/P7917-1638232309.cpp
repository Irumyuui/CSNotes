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

vector<LL>num;

void solve(){
    LL n, res = 0;
    cin >> n;
    num = vector<LL>(n);
    cin >> num[0];
    res = num[0];
    for (int i = 1; i < n; ++ i){
        cin >> num[i];
        res += labs(num[i]);
    }
    cout << res;
}

int main(){
    FAST(); 
    // FREIN("in.in");
    solve();
    return 0;
}