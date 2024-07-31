#include <cmath>
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using i64 = int64_t;

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
    
    std::vector<int> stk;
    std::vector<bool> vis(n * 2);
    auto dfs = [&](auto &dfs, int from) -> bool {
        if (vis[from ^ 1])
            return false;
        if (vis[from]) 
            return true;
        vis[from] = true;
        stk.emplace_back(from);
        for (auto to : adj[from]) {
            if (!dfs(dfs, to)) {
                return false;
            }
        }
        return true;
    };
    auto two_sat = [&](int n) {
        for (int i = 0; i < n; i += 1) {
            if (vis[i * 2] || vis[i * 2 + 1]) {
                continue;
            }
            stk.clear();
            if (!dfs(dfs, i * 2)) {
                while (!stk.empty()) {
                    vis[stk.back()] = false;
                    stk.pop_back();
                }
                if (!dfs(dfs, i * 2 + 1)) {
                    return false;
                }
            }
        }
        return true;
    };
    if (two_sat(n)) {
        for (int i = 0; i < n; i += 1) {
            if (vis[i * 2]) {
                std::cout << i * 2 + 1 << '\n';
            } else {
                std::cout << i * 2 + 2 << '\n';
            }
        }
    } else {
        std::cout << "NIE\n";
    }
}