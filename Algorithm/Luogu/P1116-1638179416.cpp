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

const int LEN = 1e5 + 5;
int arr[LEN], t[LEN];
LL ans = 0;

void mergesort(int ll, int rr){
    if (rr - ll <= 1) return;
    int mid = ll + ((rr - ll) >> 1);
    mergesort(ll, mid); mergesort(mid, rr);
    int p = ll, q = ll, r = mid;
    while (q < rr){
        if (p >= mid || (r < rr && arr[p] > arr[r]))
            t[q ++] = arr[r ++], ans += mid - p;
        else
            t[q ++] = arr[p ++];
    }
    for (int i = ll; i < rr; ++ i)
        arr[i] = t[i];
}

void solve(){
    int n;
    cin >> n;
    for (int i = 0; i < n; ++ i) cin >> arr[i];
    mergesort(0, n);
    cout << ans << endl;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}