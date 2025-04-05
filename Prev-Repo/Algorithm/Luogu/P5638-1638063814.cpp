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

const int LEN = 1e6 + 5;
LL arr[LEN];

void solve(){
    LL n, k;
    cin >> n >> k;
    LL res = -1;
    for (int i = 1; i < n; ++ i){
        LL x;
        cin >> x;
        arr[i] = arr[i - 1] + x;
        if (i >= k) res = max(res, arr[i] - arr[i - k]);
    }
    cout << arr[n - 1] - res << endl;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}