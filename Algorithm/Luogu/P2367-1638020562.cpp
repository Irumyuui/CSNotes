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

const int LEN = 5e6 + 5;
LL arr[LEN], d[LEN];

void solve(){
    LL n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++ i) cin >> arr[i];
    for (int i = 1; i <= n; ++ i) d[i] = arr[i] - arr[i - 1];
    while (q --){
        LL l, r, k;
        cin >> l >> r >> k;
        d[l] += k;
        d[r + 1] -= k;
    }
    LL midi = INFI;
    for (int i = 1; i <= n; ++ i)
        midi = min(arr[i] = arr[i - 1] + d[i], midi);
    cout << midi << endl;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}