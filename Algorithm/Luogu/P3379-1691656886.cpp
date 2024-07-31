#include <bits/stdc++.h>

#if !defined (ONLINE_JUDGE)
#  include "./include/debug.hpp"
#else
#  define debug(...)
#endif

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, q, root;
    std::cin >> n >> q >> root;
    root --;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector fa(std::bit_width<uint32_t>(n), std::vector<int>(n, -1));
    std::vector<int> dep(n);  // begin 1
    auto dfs = [&](auto &&dfs, int from, int come) -> void {
        for (int i = 1; (1 << i) <= dep[from]; i ++) {
            if (fa[i - 1][from] != -1) {
                fa[i][from] = fa[i - 1][fa[i - 1][from] ];
            } else {
                break;
            }
        }
        for (auto to : adj[from]) {
            if (to != come) {
                fa[0][to] = from;
                dep[to] = dep[from] + 1;
                dfs(dfs, to, from);
            }
        }
    };
    dep[root] = 1;
    dfs(dfs, root, -1);
    
    auto GetLca = [&](int a, int b) -> int {
        debug(a, b);
        if (dep[a] < dep[b]) {
            std::swap(a, b);
        }
        while (dep[a] > dep[b]) {
            a = fa[std::bit_width<uint32_t>(dep[a] - dep[b]) - 1][a];
        }
        if (a == b) {
            return a;
        }

        for (int i = std::bit_width<uint32_t>(dep[a]) - 1; i >= 0; i --) {
            if (fa[i][a] != fa[i][b]) {
                a = fa[i][a];
                b = fa[i][b];
            }
        }
        return fa[0][a];
    };

    for (int t = 0; t < q; t ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        std::cout << GetLca(u, v) + 1 << '\n';
    }
}