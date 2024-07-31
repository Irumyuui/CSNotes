#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
const int INFI = 0x7fffffff;

int n, m, a, b, w;
vector<vector<PII>>g;
vector<int>dist, cnt;
vector<bool>vis;

bool spfa(int sta){
    fill(dist.begin(), dist.end(), INFI);
    fill(cnt.begin(), cnt.end(), 0);
    fill(vis.begin(), vis.end(), false);
    queue<int>q;
    q.push(sta);
    dist[sta] = 0;
    vis[sta] = 1;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        vis[v] = 0;
        for (auto it : g[v]){
            if (dist[it.first] > dist[v] + it.second){
                dist[it.first] = dist[v] + it.second;
                cnt[it.first] = cnt[v] + 1;
                if (cnt[it.first] >= n + 1){
                    return false;
                }
                if (!vis[it.first]){
                    vis[it.first] = 1;
                    q.push(it.first);
                }
            }
        }
    }
    return true;
}

void solve(){
    cin >> n >> m;
    g = vector<vector<PII>>(n + 1, vector<PII>());
    vis = vector<bool>(n + 1);
    dist = cnt = vector<int>(n + 1);
    for (int i = 0; i < m; ++ i){
        cin >> a >> b >> w;
        g[b].push_back({a, w});
    }
    for (int i = 1; i <= n; ++ i){
        g[0].push_back({i, 0});
    }
    if (spfa(0)){
        for (int i = 1; i <= n; ++ i){
            cout << dist[i] << ' ';
        }
    }else{
        cout << "NO" << endn;
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