#include <bits/stdc++.h>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector adj(n * 2, std::vector<int>{});
    for (int i = 0; i < m; i ++) {
        int u, a, v, b;
        std::cin >> u >> a >> v >> b;
        u --; v --;

        // a V b => not(a) -> b ^ not(b) -> a
        adj[u * 2 + !a].emplace_back(v * 2 + b);
        adj[v * 2 + !b].emplace_back(u * 2 + a);
    }

    std::vector<int> dfn(n * 2, -1), low(n * 2, -1);
    std::stack<int, std::vector<int>> stk;
    std::vector<bool> inst(n * 2);
    std::vector<int> scc_id(n * 2);
    int scc_cnt = 0;

    auto tarjan = [&, stamp{0}](auto &&self, int from) mutable -> void {
        dfn[from] = low[from] = stamp ++;
        stk.emplace(from);
        inst[from] = true;
        for (auto to : adj[from]) {
            if (dfn[to] == -1) {
                self(self, to);
                low[from] = std::min(low[from], low[to]);
            } else if (inst[to]) {
                low[from] = std::min(low[from], dfn[to]);
            }
        }
        if (dfn[from] == low[from]) {
            int v;
            do {
                v = stk.top();
                stk.pop();
                inst[v] = false;
                scc_id[v] = scc_cnt;
            } while (v != from);
            scc_cnt ++;
        }
    };
    for (int i = 0; i < n * 2; i ++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i);
        }
    }

    bool ok = true;
    for (int i = 0; i < n && ok; i ++) {
        ok &= scc_id[i * 2] != scc_id[i * 2 + 1];
    }

    if (!ok) {
        std::cout << "IMPOSSIBLE\n";
    } else {
        std::cout << "POSSIBLE\n";
        for (int i = 0; i < n; i ++) {
            int ret = scc_id[i * 2] > scc_id[i * 2 + 1];
            std::cout << ret << " \n"[i + 1 == n];
        }
    }
}