#include <iostream>
#include <vector>
#include <algorithm>

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

    std::vector col(n, 0);
    for (int i = 0; i < n; i ++) {
        std::cin >> col[i];
        col[i] --;
    }

    std::vector<int> dfn(n, -1), rnk(n, -1), siz(n), son(n);
    auto dfs1 = [&, stamp{-1}](auto &&dfs, int from) mutable -> void {
        dfn[from] = ++ stamp;
        rnk[stamp] = from;
        siz[from] = 1;
        son[from] = -1;
        for (auto to : adj[from]) {
            if (dfn[to] == -1) {
                dfs(dfs, to);
                siz[from] += siz[to];
                if (son[from] == -1 || siz[to] > siz[son[from]]) {
                    son[from] = to;
                }
            }
        }
    };
    dfs1(dfs1, 0);

    for (int i = 0; i < n; i ++) {
        // std::cerr << dfn[i] << ' ' << rnk[i] << ' ' << siz[i] << ' ' << son[i] << '\n';
    }

    std::vector<int> col_cnt(std::ranges::max(col) + 1);
    int ret = 0;
    auto Add = [&](int v) {
        if (!col_cnt[col[v]]) {
            ret ++;
        }
        col_cnt[col[v]] ++;
    };
    auto Del = [&](int v) {
        col_cnt[col[v]] --;
        if (col_cnt[col[v]] == 0) {
            ret --;
        } 
    };

    std::vector<int> ans(n);
    auto dfs2 = [&](auto &&dfs, int from, int come, bool keep) -> void {
        // std::cerr << from << ' ' << come << '\n';
        for (auto to : adj[from])
            if (to != come && to != son[from])
                dfs(dfs, to, from, false);
        if (son[from] != -1) {
            dfs(dfs, son[from], from, true);
            for (auto to : adj[from]) {
                if (to != come && to != son[from])
                    for (int i = dfn[to]; i < dfn[to] + siz[to]; i ++)
                        Add(rnk[i]);
            }
        }
        Add(from);
        ans[from] = ret;
        if (!keep)
            for (int i = dfn[from]; i < dfn[from] + siz[from]; i ++)
                Del(rnk[i]);
    };
    dfs2(dfs2, 0, -1, false);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; i ++) {
        int x;
        std::cin >> x;
        x -= 1;
        std::cout << ans[x] << '\n';
    }

    // for (int i = 0; i < n; i ++) {
    //     std::cout << ans[i] << " \n"[i + 1 == n];
    // }
}
