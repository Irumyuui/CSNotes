#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
using ll = long long;

vector< vector< pair<int, int> > >g;
vector<int>dist;
vector<bool>vis;

inline void adde(int &u, int &v, int &w) {
    g[u].push_back({v, w});
}

void dijksta(int sta) {
    dist[sta] = 0;
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> >>q;
    q.push({dist[sta], sta});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (const auto &[v, w] : g[u]) {
            if (!vis[v] & dist[v] > max(dist[u], w)) {
                dist[v] = max(dist[u], w);
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, m, s, t;
    cin >> n >> m >> s >> t;

    g.assign(n + 1, vector< pair<int, int> >());
    dist.assign(n + 1, 1 << 30);
    vis.assign(n + 1, false);

    for (int i = 1; i <= m; ++ i) {
        int u, v, w;
        cin >> u >> v >> w;
        adde(u, v, w);
        adde(v, u, w);
    }

    dijksta(s);

    cout << dist[t];

    return 0;
}