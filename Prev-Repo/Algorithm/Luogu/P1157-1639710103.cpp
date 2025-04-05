#include <bits/stdc++.h>
#define INFI 0x7fffffff
#define INFL 0x7fffffffffffffff
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

int n, r;
set<vector<int>>s;

vector<int>v;
void dfs(int i){
    if (v.size() == r){
        s.insert(v);
        return;
    }
    for (int k = i; k <= n; ++ k){
        v.push_back(k);
        dfs(k + 1);
        v.pop_back();
    }
}

void solve(){
    dfs(1);
    for (auto it : s){
        for (auto _ : it){
            cout << setw(3) << _;
        }
        cout << endl;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n >> r;
    solve();
    return 0;
}