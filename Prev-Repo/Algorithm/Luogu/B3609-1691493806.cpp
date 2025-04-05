#include <bits/stdc++.h>
using namespace std;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;

    std::vector adj(n, std::vector<int>{});
    for (int i = 0; i < m; i ++) {
        int u, v;
        std::cin >> u >> v;
        u --; v --;
        adj[u].emplace_back(v);
    }

    std::vector<int> dfn(n, -1), low(n, -1);
    std::stack<int,std::vector<int>> stk;
    std::vector<bool> inst(n);
    std::vector<std::vector<int>> scc;
    // std::vector<int> scc_id(n);
    
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
        if (low[from] == dfn[from]) {
            int v;
            scc.emplace_back(std::vector<int>{});
            do {
                v = stk.top();
                stk.pop();
                inst[v] = false;
                scc.back().emplace_back(v);
            } while (v != from);
        }
    };

    for (int i = 0; i < n; i ++) {
        if (dfn[i] == -1) {
            tarjan(tarjan, i);
        }
    }

    for (auto &ls : scc) {
        std::ranges::sort(ls);
    }
    std::ranges::sort(scc);

    std::cout << scc.size() << '\n';
    for (auto &&ls : scc) {
        for (auto &x : ls) {
            std::cout << x + 1 << ' ';
        }
        std::cout << '\n';
    }
}