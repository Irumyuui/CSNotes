#include <bits/stdc++.h>
#define INFI 0x7fffffff
#define INFL 0x7fffffffffffffff
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

int n;
vector<int>v1, v2;
priority_queue<PII, vector<PII>, greater<PII>>q;

void solve(){
    for (auto it : v2){
        q.push({it + v1[0], 0});
    }
    for (int i = 0; i < n; ++ i){
        PII x = q.top();
        cout << q.top().first << ' ';
        q.pop();
        q.push({x.first - v1[x.second] + v1[x.second + 1], x.second + 1});
    }
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n;
    v1 = v2 = vector<int>(n);
    for (auto &it : v1) cin >> it;
    for (auto &it : v2) cin >> it;
    solve();
    return 0;
}