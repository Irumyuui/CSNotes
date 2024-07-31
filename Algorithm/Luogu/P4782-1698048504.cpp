#include <cmath>

#include <iostream>
#include <vector>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n, m;
    std::cin >> n >> m;
    
    // a -> b => not a V b
    // 2 * u := not true; 2 * u + 1 := true
    std::vector adj(n * 2, std::vector<int>{});
    for (int i = 0; i < m; i += 1) {
        int u, uw, v, vw;
        std::cin >> u >> uw >> v >> vw;
        u -= 1; v -= 1;
        adj[u * 2 + !uw].emplace_back(v * 2 + vw);
        adj[v * 2 + !vw].emplace_back(u * 2 + uw);
    }
    
    std::vector<int> dfn(n * 2, -1), low(dfn), scc_id(dfn);
    int scc_cnt = 0;
    std::vector<int> stk;
    std::vector<bool> inst(n * 2);
    
    auto trajan = [&, stamp{0}](auto &self, int from) mutable -> void {
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
            trajan(trajan, i);
        }
    }
    
    // scc_id 是反的拓扑序
    // 让拓扑序在后的节点作为选择结果
    for (int i = 0; i < n; i += 1) {
        if (scc_id[i * 2] == scc_id[i * 2 + 1]) {
            std::cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    std::cout << "POSSIBLE\n";
    for (int i = 0; i < n; i += 1) {
        auto ret = scc_id[i * 2] < scc_id[i * 2 + 1];
        if (ret) {
            std::cout << 0 << ' ';
        } else {
            std::cout << 1 << ' ';
        }
    }
    std::cout << '\n';
}