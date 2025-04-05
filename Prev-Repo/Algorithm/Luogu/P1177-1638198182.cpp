#include <bits/stdc++.h>

using namespace std;
map<int, int>m;

void solve(){
    int n, x;
    cin >> n;
    for (int i = 0; i < n; ++ i){
        cin >> x;
        m[x] ++;
    }
    for (auto it : m)
        for (int i = 0; i < it.second; ++ i)
            cout << it.first << ' ';
}

int main(){
    std::ios::sync_with_stdio(false);
    solve();
    return 0;
}