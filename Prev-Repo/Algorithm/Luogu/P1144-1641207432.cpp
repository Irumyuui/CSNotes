#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

const LL MOD = 100003;
LL n, m, a, b;
vector<vector<LL>>g;
vector<LL>dist, cnt;
vector<bool>vis;

void solve(){
    cin >> n >> m;
    g = vector<vector<LL>>(n + 1, vector<LL>());
    dist = cnt = vector<LL>(n +1, 0);
    vis = vector<bool>(n + 1, false);
    for (int i = 0; i < m; ++ i){
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    fill(dist.begin(), dist.end(), 0x7FFFFFFFFFFFFFFF);
    cnt[1] = 1;
    dist[1] = 0;
    priority_queue<PLL, vector<PLL>, greater<PLL>>q;
    q.push({dist[1], 1});
    while (!q.empty()){
        int v = q.top().second;
        q.pop();
        if (vis[v]) continue;
        vis[v] = 1;
        for (auto it : g[v]){
            if (!vis[it]){
                if(dist[it] > dist[v] + 1){
                    dist[it] = dist[v] + 1;
                    cnt[it] = cnt[v];
                    q.push({dist[it], it});
                }else if (dist[it] == dist[v] + 1){
                    cnt[it] += cnt[v];
                }
                cnt[it] %= MOD;
            }
        }
    }
    for (int i = 1; i <= n; ++ i){
        if (vis[i])
            cout << cnt[i] << endn;
        else
            cout << 0 << endn;
    }
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