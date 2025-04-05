#include <bits/stdc++.h>
using namespace std;

vector< vector< pair<int, int> > >g;
vector<int>dist;
vector<bool>vis;

inline void add(int &u, int &v, int &w) {
    g[u].push_back({v, w});
}

void dijkstra(int sta, bool flag) {
    dist[sta] = 0;
    
    priority_queue<pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > >q;

    q.push({dist[sta], sta});

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (const auto &[v, w] : g[u]) {
            if (dist[v] >= dist[u] ^ w || flag) {
                dist[v] = dist[u] ^ w;
                q.push({dist[v], v});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, Q;
    cin >> n >> m >> Q;

    g = vector< vector< pair<int, int> > >(n + 1, vector< pair<int, int> >());
    vis = vector<bool>(n + 1, false);
    dist = vector<int>(n + 1, 1 << 30);

    int cnt = 0;
    for (int i = 1; i <= m; ++ i) {
        int u, v, w;
        cin >> u >> v >> w;
        
        add(u, v, w);
        add(v, u, w);

        if (w <= 1) {
            cnt ++;
        }
    }

    dijkstra(1, cnt == m);

    for (int i = 1; i <= Q; ++ i) {
        int u, v;
        cin >> u >> v;

        cout << (dist[u] ^ dist[v]) << '\n';
    }

    return 0;
}