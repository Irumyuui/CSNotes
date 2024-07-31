#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, s;
    std::cin >> n >> m >> s;
    std::vector<int> dfn(n + 1, -1), rnk(n + 1, -1), dep(n + 1, -1), siz(n + 1, -1), fa(n + 1, -1), top(n + 1, -1), son(n + 1, -1);
    std::vector edge(n + 1, std::vector<int>());
    for (int i = 0; i < n - 1; i ++) {
        int from, to;
        std::cin >> from >> to;
        edge[from].push_back(to);
        edge[to].push_back(from);
    }
    int stamp{};
    auto dfs1 = [&](auto &&dfs, int from) -> void {
        siz[from] = 1;
        son[from] = -1;
        for (auto to : edge[from]) {
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
    auto dfs2 = [&](auto &&dfs, int from, int root) -> void {
        top[from] = root;
        dfn[from] = ++ stamp;
        rnk[stamp] = from;
        if (son[from] == -1) {
            return;
        }
        dfs(dfs, son[from], root);
        for (auto to : edge[from]) {
            if (son[from] != to && fa[from] != to) {
                dfs(dfs, to, to);
            }
        }
    };
    dep[s] = 0;
    dfs1(dfs1, s);
    dfs2(dfs2, s, s);
    auto Lca = [&](int a, int b) -> int {
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
    while (m --) {
        int a, b;
        std::cin >> a >> b;
        std::cout << Lca(a, b) << '\n';
    }
}