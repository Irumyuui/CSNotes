#include <bits/stdc++.h>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m, d;
    std::cin >> n >> m >> d;
    std::vector adj(n, std::vector<std::tuple<int,int,int>>{});
    for (int i = 0; i < m; i ++) {
        int u, v, sp, len;
        std::cin >> u >> v >> sp >> len;
        adj[u].emplace_back(v, sp, len);
        // adj[v].emplace_back(u, sp, len);
    }
    
    int max_sp = 70;
    for (auto &list : adj) {
        for (auto &[_, sp, __] : list) {
            max_sp = std::max(max_sp, sp);
        }
    }
    
    std::vector dis(n, std::vector<double>(max_sp + 1, inf<int>));
    std::vector vis(n, std::vector<bool>(max_sp + 1));
    std::vector come(n, std::vector<std::pair<int,int>>(max_sp + 1, {-1, -1}));
    dis[0][70] = 0;
    std::priority_queue<std::tuple<double,int,int>, std::vector<std::tuple<double,int,int>>,
        std::greater<std::tuple<double,int,int>>> pq;
    pq.emplace(0, 0, 70);
    
    while (!pq.empty()) {
        auto [__, from, come_V] = pq.top();
        pq.pop();
        if (vis[from][come_V])
            continue;
        vis[from][come_V] = true;
        for (auto [to, lim_V, len] : adj[from]) {
            auto next_V = lim_V == 0 ? come_V : lim_V;
            if (auto ret = dis[from][come_V] + (double)len / next_V;
                !vis[to][next_V] && dis[to][next_V] > ret
            ) {
                dis[to][next_V] = ret;
                come[to][next_V] = std::pair{from, come_V};
                pq.emplace(dis[to][next_V], to, next_V);
            }
        }
    }
    
    double min_dis = inf<int>;
    int tag_sp = -1;
    for (int i = 1; i <= max_sp; i ++) {
        if (dis[d][i] < min_dis) {
            min_dis = dis[d][i];
            tag_sp = i;
        }
    }
    // std::cout << min_dis << " " << tag_sp << '\n';
    
    auto Write = [&](auto &dfs, int from, int v) -> void {
        // std::cout << "from = " << from << " v = " << v << '\n';
        if (from == 0) {
            std::cout << from << ' ';
            return;
        }
        auto [to, nex_v] = come[from][v];
        dfs(dfs, to, nex_v);
        std::cout << from << ' ';
    };
    Write(Write, d, tag_sp);
    std::cout << '\n';
}