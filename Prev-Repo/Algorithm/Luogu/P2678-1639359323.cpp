#include <bits/stdc++.h>
using namespace std;
const int INFI = 0x7FFFFFFF;
const long long INFLL = 0x7FFFFFFFFFFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

const int LEN = 5e4 + 115;
int len, n, m;
int stone[LEN] = {0, };

bool check(int jlen){
    int cnt = 0, place = 0;
    for (int i = 1; i <= n + 1; ++ i){
        if (stone[i] - stone[place] < jlen) cnt ++;
        else place = i;
    }
    if (cnt > m)
        return false;
    else
        return true;
}

void solve(){
    int ll, rr, ans, mid;
    ll = 0, rr = len;
    while (ll <= rr){
        mid = ll + ((rr - ll) >> 1);
        if (check(mid)){
            ans = mid;
            ll = mid + 1;
        }else{
            rr = mid - 1;
        }
    }
    cout << ans << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    cin >> len >> n >> m;
    for (int i = 1; i <= n; ++ i) cin >> stone[i];
    stone[n + 1] = len;
    sort(stone + 1, stone + n + 1, less<int>());
    solve();
    return 0;
}