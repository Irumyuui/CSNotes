#include <cmath>
#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector adj(n * 2, std::vector<int>{});
    for (int i = 0; i < m; i += 1) {
        int u, v;
        std::cin >> u >> v;
        u -= 1; v -= 1;
        adj[u].emplace_back(v ^ 1);
        adj[v].emplace_back(u ^ 1);
    }
    
    std::vector dfn(n * 2, -1), low(dfn), scc_id(dfn);
    std::vector<int> stk;
    std::vector<bool> inst(n * 2);
    int scc_cnt = 0;
    
    auto tarjan = [&, stamp{0}](auto &self, int from) mutable -> void {
        dfn[from] = low[from] = stamp;
        stamp += 1;
        stk.emplace_back(from);
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
                v = stk.back();
                stk.pop_back();
                inst[v] = false;
                scc_id[v] = scc_cnt;
            } while (v != from);
            scc_cnt += 1;
        }
    };
    for (int i = 0; i < n * 2; i += 1) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i);
        }
    }
    
    for (int i = 0; i < n; i += 1) {
        if (scc_id[i * 2] == scc_id[i * 2 + 1]) {
            std::cout << "NIE\n";
            return 0;
        }
    }
    
    for (int i = 0; i < n; i += 1) {
        if (scc_id[i * 2] < scc_id[i * 2 + 1]) {
            std::cout << i * 2 + 1 << '\n';
        } else {
            std::cout << i * 2 + 2 << '\n';
        }
    }
}