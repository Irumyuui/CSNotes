#include <bits/stdc++.h>
using namespace std;

int n, p, x;
map<int, int>a;
vector<int>b, res;

void solve(){
    cin >> n;
    for (int i = 0; i < n; ++ i){
        cin >> x;
        a[x] = i;
    }
    cin >> x;
    res.push_back(a[x]);
    for (int i = 1; i < n; ++ i){
        cin >> x;
        p = a[x];
        if (p > res.back()){
            res.push_back(p);
        }else{
            auto it = lower_bound(res.begin(), res.end(), p);
            *it = p;
        }
    }
    cout << res.size() << endl;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}