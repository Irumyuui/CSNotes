#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

int n, m, s;
vector<vector<PII>>g;
vector<int>dist;
vector<bool>vis;

void spfa(int sta){
    fill(dist.begin(), dist.end(), 0x7FFFFFFF);
    fill(vis.begin(), vis.end(), false);
    dist[sta] = 0;
    vis[sta] = true;
    queue<int>q;
    q.push(sta);
    while (!q.empty()){
        int v = q.front();
        q.pop();
        vis[v] = false;
        for (auto it : g[v]){
            if (dist[it.first] > dist[v] + it.second){
                dist[it.first] = dist[v] + it.second;
                if (!vis[it.first]){
                    q.push(it.first);
                    vis[it.first] = true;
                }
            }
        }
    }
}

void solve(){
    cin >> n >> m >> s;
    g = vector<vector<PII>>(n + 1, vector<PII>());
    vis = vector<bool>(n + 1, false);
    dist = vector<int>(n + 1);
    for (int i = 0; i < m; ++ i){
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
    }
    spfa(s);
    for (int i = 1; i <= n; ++ i){
        cout << dist[i] << ' ';
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