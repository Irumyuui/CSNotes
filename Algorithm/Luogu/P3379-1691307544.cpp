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

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < n - 1; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    root --;

    std::vector<int> dep(n, -1), top(dep), fa(dep), son(dep), siz(dep), dfn(dep), rnk(dep);
    auto Build = [&](int root) -> void {
        auto dfs1 = [&](auto &&dfs, int from) -> void {
            siz[from] = 1;
            son[from] = -1;
            for (auto to : adj[from]) {
                if (dep[to] != -1) continue;
                dep[to] = dep[from] + 1;
                fa[to] = from;
                dfs(dfs, to);
                siz[from] += siz[to];
                if (son[from] == -1 || siz[to] > siz[son[from]])
                    son[from] = to;
            }
        };
        auto dfs2 = [&, stamp{-1}](auto &&dfs, int from, int link_top) mutable -> void {
            top[from] = link_top;
            dfn[from] = ++ stamp;
            rnk[stamp] = from;
            if (son[from] == -1)
                return;
            dfs(dfs, son[from], link_top);
            for (auto to : adj[from]) 
                if (to != son[from] && to != fa[from])
                    dfs(dfs, to, to);
        };
        // std::fill(std::begin(dep), std::end(dep), -1);
        dep[root] = 0;
        dfs1(dfs1, root);
        dfs2(dfs2, root, root);
    };
    Build(root);

    // std::vector<int> dep(n, -1), top(dep), fa(dep), son(dep), siz(dep), dfn(dep), rnk(dep);
    // auto Build = [&](int root) -> void {
    //     auto dfs1 = [&](auto &&dfs, int from) -> void {
    //         debug(from);
    //         siz[from] = 1;
    //         son[from] = -1;
    //         for (auto to : adj[from]) {
    //             if (dep[to] == -1) {
    //                 dep[to] = dep[from] + 1;
    //                 fa[to] = from;
    //                 dfs(dfs, to);
    //                 siz[from] += siz[to];
    //                 if (son[from] == -1 || siz[to] > siz[son[from]])
    //                     son[from] = to;
    //             }
    //         }
    //     };
    //     auto dfs2 = [&, stamp{-1}](auto &&dfs, int from, int link_top) mutable -> void {
    //         debug(from, link_top);
    //         top[from] = link_top;
    //         dfn[from] = ++ stamp;
    //         rnk[stamp] = from;
    //         if (son[from] == -1) {
    //             return;
    //         }
    //         dfs(dfs, son[from], link_top);
    //         for (auto to : adj[from]) {
    //             if (to != son[from] && to != fa[from]) {
    //                 dfs(dfs, to, to);
    //             }
    //         }
    //     };

    //     // std::fill(dep.begin(), dep.end(), -1);
    //     dep[root] = 0;
    //     dfs1(dfs1, root);
    //     dfs2(dfs2, root, root);
    // };
    // Build(root);

    debug(dep, top, fa, son, siz);

    auto GetLca = [&](int a, int b) {
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]]) {
                std::swap(a, b);
            }
            a = fa[top[a]];
        }
        if (dep[a] > dep[b])
            std::swap(a, b);
        return a;
    };

    for (int t = 0; t < q; t ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        debug(u, v);
        std::cout << GetLca(u, v) + 1 << '\n';
    }
}