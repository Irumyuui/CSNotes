#include <bits/stdc++.h>
#define endn "\n"
using namespace std;

int x, k;

void solve(){
    int i = 1;
    while (k > 1){
        cout << i << ' ' << 0 << endn;
        i ++;
        k --;
        x -= 1;
    }
    cout << x << ' ' << 1 << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> x >> k;
    solve();
    return 0;
}