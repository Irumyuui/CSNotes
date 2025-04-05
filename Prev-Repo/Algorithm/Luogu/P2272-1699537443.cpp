#include <bits/stdc++.h>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;;
    i64 mod;
    std::cin >> n >> m >> mod;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < m; i ++) {
        int from, to;
        std::cin >> from >> to;
        from --; to --;
        adj[from].emplace_back(to);
    }


    std::vector<int> dfn(n, -1), low(n, -1), scc_id(n, -1);
    std::vector<bool> inst(n);
    std::vector<int> stk;
    stk.reserve(n);
    int scc_cnt = 0;

    auto dfs = [&, stamp{0}](auto &dfs, int from) mutable -> void {
        dfn[from] = low[from] = ++ stamp;
        stk.emplace_back(from);
        inst[from] = true;
        for (auto to : adj[from]) {
            if (dfn[to] == -1) {
                dfs(dfs, to);
                low[from] = std::min(low[from], low[to]);
            } else if (inst[to]) {
                low[from] = std::min(low[from], dfn[to]);
            }
        }
        if (low[from] == dfn[from]) {
            int v;
            do {
                v = stk.back();
                stk.pop_back();
                inst[v] = false;
                scc_id[v] = scc_cnt;
            } while (v != from);
            scc_cnt ++;
        }
    };
    for (int i = 0; i < n; i ++) {
        if (dfn[i] == -1) {
            dfs(dfs, i);
        }
    }

    std::vector<int> scc_siz(scc_cnt);
    std::vector scc_adj(scc_cnt, std::vector<int>{});
    std::vector<int> indeg(scc_cnt), outdeg(scc_cnt);
    for (int i = 0; i < n; i ++) {
        scc_siz[scc_id[i]] ++;
        for (auto j : adj[i]) {
            if (scc_id[i] != scc_id[j]) {
                scc_adj[scc_id[i]].emplace_back(scc_id[j]);                
            }
        }
    }
    for (int i = 0; auto &list : scc_adj) {
        std::ranges::sort(list);
        list.erase(std::ranges::unique(list).begin(), list.end());
        for (auto x : list) {
            indeg[x] ++;
            outdeg[i] ++;
        }
        i ++;
    }

    std::queue<int> q;
    std::vector<i64> f(scc_cnt), g(scc_cnt);
    std::vector<int> out_list;
    for (int i = 0; i < scc_cnt; i ++) {
        if (indeg[i] == 0) {
            q.emplace(i);
            f[i] = scc_siz[i];
            g[i] = 1;
        }
        if (!outdeg[i]) {
            out_list.emplace_back(i);
        }
    }

    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (auto to : scc_adj[from]) {
            if (f[to] < f[from] + scc_siz[to]) {
                f[to] = f[from] + scc_siz[to];
                g[to] = g[from];
            } else if (f[to] == f[from] + scc_siz[to]) {
                (g[to] += g[from]) %= mod;
            }
            if (-- indeg[to] == 0) {
                q.emplace(to);
            }
        }
    }

    i64 ans1 = 0, ans2 = 0;
    for (auto x : out_list) {
        if (f[x] > ans1) {
            std::tie(ans1, ans2) = {f[x], g[x]};
        } else if (f[x] == ans1) {
            (ans2 += g[x]) %= mod;
        }
    }

    std::cout << ans1 << '\n' << ans2 << '\n';
}
