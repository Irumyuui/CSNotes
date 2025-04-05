#include <bits/stdc++.h>
using namespace std;

#define all(X) std::begin(X), std::end(X)
#define cauto const auto
#define endn '\n'

constexpr int INF = 1 << 30;

using ll = long long;
using LL = __int128_t;

vector<vector<pair<int, int>>>g;
vector<int>dist;
vector<bool>vis;

void dijkstar(int sta, int end) {
    fill(all(vis), false);
    fill(all(dist), INF);

    dist[sta] = 0;
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > >q;
    q.push({dist[sta], sta});

    while (!q.empty()) {
        int now = q.top().second;
        q.pop();
        if (vis[now]) 
            continue;
        vis[now] = true;

        for (cauto &[v, w] : g[now]) {
            if ((now == sta && v == end) || (now == end && v == sta)) {
                continue;
            }
            if (!vis[v] && dist[v] > dist[now] + w) {
                dist[v] = dist[now] + w;
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, m;
    cin >> n >> m;
    g.assign(n + 1, vector<pair<int, int>>());
    dist.assign(n + 1, 0);
    vis.assign(n + 1, false);

    for (int i = 0; i < m; ++ i) {
        int u, v ,w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    int ans = INF;
    for (int sta = 1; sta <= n; ++ sta) {
        for (cauto &[end, w] : g[sta]) {
            dijkstar(sta, end);
            ans = min(ans, dist[end] + w);
        }
    }

    if (ans == INF) {
        cout << "No solution.";
    } else {
        cout << ans;
    }

    return 0;
}