#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const int LEN = 1e6 + 5;
LL ll = 0, rr = 0, n, m;
LL woods[LEN] = {0, };

void solve(){
    cin >> n >> m;
    for (int i = 0; i < n; ++ i){
        cin >> woods[i];
        rr = max(woods[i], rr);
    }
    while (ll <= rr){
        LL mid = ll + ((rr - ll) >> 1);
        LL k = 0;
        for (int i = 0; i < n; ++ i)
            k += woods[i] > mid ? woods[i] - mid : 0;
        if (k < m) rr = mid - 1;
        else ll = mid + 1;
    }
    cout << ll - 1 << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}