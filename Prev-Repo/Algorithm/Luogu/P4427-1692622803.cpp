#include "bits/stdc++.h"

using i64 = int64_t;

constexpr i64 MOD = 998244353;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    std::cin >> n;
    
    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    std::vector<int> dep(n, -1), top(n), son(n), fa(n, -1), siz(n);
    std::vector pre_sum(n, std::array<i64,51>{});

    auto build = [&](int root) -> void {
        auto dfs1 = [&](auto &dfs, int from) -> void {
            pre_sum[from][0] = 1;
            for (int i = 1; i < pre_sum[from].size(); i ++) {
                pre_sum[from][i] = pre_sum[from][i - 1] * dep[from] % MOD;
            }

            son[from] = -1;
            siz[from] = 1;
            for (auto to : adj[from]) {
                if (dep[to] == -1) {
                    dep[to] = dep[from] + 1;
                    fa[to] = from;
                    dfs(dfs, to);
                    siz[from] += siz[to];
                    if (son[from] == -1 || siz[to] > siz[son[from]]) {
                        son[from] = to;
                    }
                }
            }
        };
        auto dfs2 = [&](auto &dfs, int from, int link_top) -> void {
            top[from] = link_top;
            if (son[from] == -1) {
                return;
            }
            for (int i = 0; i < pre_sum[from].size(); i ++) {
                (pre_sum[son[from]][i] += pre_sum[from][i]) %= MOD;
            }
            dfs(dfs, son[from], link_top);
            for (auto to : adj[from]) {
                if (to != son[from] && to != fa[from]) {
                    for (int i = 0; i < pre_sum[from].size(); i ++) {
                        (pre_sum[to][i] += pre_sum[from][i]) %= MOD;
                    }
                    dfs(dfs, to, to);
                }
            }
        };

        dep[root] = 0;
        dfs1(dfs1, root);
        dfs2(dfs2, root, root);
    };
    build(0);

    auto GetLca = [&](int a, int b) -> int {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) {
                std::swap(a, b);
            }
            a = fa[top[a]];
        }
        if (dep[a] > dep[b]) {
            std::swap(a, b);
        }
        return a;
    };

    int q;
    std::cin >> q;

    for (int test = 0; test < q; test ++) {
        int a, b, k;
        std::cin >> a >> b >> k;
        a --; b --;
    
        auto lca = GetLca(a, b);
        auto ret = (((pre_sum[a][k] + pre_sum[b][k]) % MOD - pre_sum[lca][k]) % MOD + MOD) % MOD;   
        if (lca != 0) {
            (((ret -= pre_sum[fa[lca]][k]) %= MOD) += MOD) %= MOD;
        }

        std::cout << ret << '\n';
    }
}