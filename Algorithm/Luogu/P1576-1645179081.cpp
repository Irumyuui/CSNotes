#include <bits/stdc++.h>

std::vector< std::vector< std::pair<int, double> > >g;
std::vector<double>dist;
std::vector<bool>vis;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    g.assign(n + 1, std::vector<std::pair<int, double>>());
    dist.assign(n + 1, double(1ll << 60));
    vis.assign(n + 1, false);

    for (int i = 1; i <= m; ++ i) {
        int a, b;
        double w;
        std::cin >> a >> b >> w;

        g[a].push_back({b, w * 0.01});
        g[b].push_back({a, w * 0.01});
    }

    int sta, end;
    std::cin >> sta >> end;

    dist[end] = 100;

    std::priority_queue<std::pair<double, int>,
                        std::vector<std::pair<double, int>>,
                        std::greater<std::pair<double, int>>>q;
    q.push(std::pair<double, int>(dist[end], end));

    while (!q.empty()) {
        int u = q.top().second;
        q.pop();

        if (vis[u]) {
            continue;
        }
        vis[u] = true;

        for (const auto &[v, w] : g[u]) {
            if (!vis[v] && dist[v] > dist[u] / (1.0 - w)) {
                dist[v] = dist[u] / (1.0 - w);
                q.push(std::pair<double, int>(dist[v], v));
            }
        }
    }

    std::cout << std::fixed << std::setprecision(8) << dist[sta] << '\n';

    return 0;
}