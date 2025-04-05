#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m, e;
    std::cin >> n >> m >> e;

    std::vector adj(n + m, std::vector<int>{});
    for (int i = 0; i < e; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v + n);
        adj[v + n].emplace_back(u);
    }

    std::vector<int> match(n + m, -1);
    std::vector<bool> vis(n + m);
    
    auto dfs = [&](auto &&dfs, int from) -> bool {
        for (auto to : adj[from]) {
            if (!vis[to]) {
                vis[to] = true;
                if (match[to] == -1 || dfs(dfs, match[to])) {
                    match[to] = from;
                    return true;
                }
            }
        }
        return false;
    };

    int cnt = 0;
    for (int i = 0; i < n; i ++) {
        std::fill(vis.begin(), vis.end(), false);
        cnt += dfs(dfs, i);
    }

    std::cout << cnt << '\n';
}