#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int LEN = 1e5 + 5;
LL n, k, ll = 0, rr = 0;
LL woods[LEN] = {0, };

bool cancut(LL len){
    if (len == 0) return false;
    LL cnt = 0;
    for (int i = 0; i < n; ++ i) cnt += woods[i] / len;
    if (cnt >= k) return true;
    return false;
}

void solve(){
    cin >> n >> k;
    for (int i = 0; i < n; ++ i){
        cin >> woods[i];
        rr = max(rr, woods[i]);
    }
    while (ll <= rr){
        LL mid = ll + ((rr - ll) >> 1);
        if (cancut(mid)){
            ll = mid + 1;
        }else{
            rr = mid - 1;
        }
    }
    cout << (ll > 0 ? ll - 1 : 0) << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}