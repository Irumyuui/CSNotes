#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const LL MOD = 80112002;
LL n, m, a, b, v, ans = 0;;
vector<vector<LL>>g;
vector<LL>ind, outd, dist;
queue<LL>q;

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n >> m;
    g = vector<vector<LL>>(n + 1, vector<LL>());
    ind = outd = dist = vector<LL>(n + 1, 0);
    for (int i = 1; i <= m; ++ i){
        cin >> a >> b;
        g[a].push_back(b);
        ind[b] ++;
        outd[a] ++;
    }
    for (int i = 1; i <= n; ++ i){
        if (ind[i] == 0){
            dist[i] = 1;
            q.push(i);
        }
    }
    while (!q.empty()){
        v = q.front();
        q.pop();
        for (auto nex : g[v]){
            dist[nex] = (dist[nex] + dist[v]) % MOD;
            if (-- ind[nex] == 0)
                q.push(nex);
        }
    }
    for (int i = 1; i <= n; ++ i){
        if (outd[i] == 0)
            ans = (ans + dist[i]) % MOD;
    }
    cout << ans << endn;
    return 0;
}