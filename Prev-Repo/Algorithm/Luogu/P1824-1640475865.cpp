#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e5 + 115;
int n, m;
LL arr[LEN], ll, rr;

bool check(LL len){
    int cnt = 1, p = 0;
    for (int i = 1; i < n; ++ i){
        if (arr[p] + len <= arr[i]){
            p = i;
            cnt ++;
        }
    }
    if (cnt >= m){
        return true;
    }
    return false;
}

void solve(){
    LL ans = 0;
    ll = 0, rr = arr[n - 1] - arr[0];
    while (ll <= rr){
        LL mid = ll + ((rr - ll) >> 1);
        if (check(mid)){
            ans = max(ans, mid);
            ll = mid + 1;
        }else{
            rr = mid - 1;
        }
    }
    cout << ans << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 0; i < n; ++ i){
        cin >> arr[i];
    }
    sort(arr, arr + n, less<LL>());
    solve();
    return 0;
}