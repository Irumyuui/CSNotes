#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
using ll = long long;

vector< vector< pair<int, int> > >g;
vector<int>dist, cnt;
vector<bool>vis;

int n;

inline void addedge(int &u, int &v, int &w){
    g[u].push_back({v, w});
}

bool spfa(int sta = 1){
    dist[sta] = 0;
    vis[sta] = true;
    cnt[sta] = 0;

    queue<int>q;
    q.push(sta);

    while (!q.empty()){
        int u = q.front();
        q.pop();
        vis[u] = false;

        for (const auto &[v, w] : g[u]){
            if (dist[v] < dist[u] + w){
                dist[v] = dist[u] + w;
                cnt[v] = cnt[u] + 1;
                
                if (cnt[v] >= n){
                    return false;
                }
                if (!vis[v]){
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int m;
    cin >> n >> m;

    g = vector<vector<pair<int, int>>>(n + 1, vector<pair<int, int>>());
    dist = vector<int>(n + 1, -(1 << 30));
    cnt = vector<int>(n + 1, 0);
    vis = vector<bool>(n + 1, false);

    while (m --){
        int u, v, w;
        cin >> u >> v >> w;
        addedge(u, v, w);
        // addedge(v, u, w);
    }

    spfa(1);

    if (dist[n] == -(1 << 30)){
        cout << -1;
    }else{
        cout << dist[n] << '\n';
    }

    return 0;
}