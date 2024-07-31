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

int m, n;
vector<LL>sch;
LL ans = 0;

int bsearch(int x){
    int ll = 0, rr = m - 1;
    while (ll <= rr){
        int mid = ll + ((rr - ll) >> 1);
        if (x > sch[mid])
            ll = mid + 1;
        else if (x < sch[mid])
            rr = mid - 1;
        else
            return mid;
    }
    return ll;
}

void solve(){
    for (int i = 0; i < n; ++ i){
        LL x;
        cin >> x;
        int it = bsearch(x);
        if (it == 0){
            ans += abs(x - sch[it]);
        }else if (it == m){
            ans += abs(x - sch.back());
        }else{
            ans += min(abs(x - sch[it]), abs(x - sch[it - 1]));
        }
    }
    cout << ans << endl;
}

int main(){
    FAST(); 
    //FREIN("in.in");
    cin >> m >> n;
    sch = vector<LL>(m);
    for (auto &it : sch) cin >> it;
    sort(sch.begin(), sch.end(), less<int>());
    solve();
    return 0;
}