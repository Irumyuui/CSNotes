#include <bits/stdc++.h>

void Main() {
    int n, m;
    std::cin >> n >> m;

    std::vector adj(n * 2, std::vector<int>{});
    // u -> v => not u V v
    for (int i = 0; i < m; i += 1) {
        char k1, k2;
        int u, v;
        std::cin >> k1 >> u >> k2 >> v;
        u -= 1; v -= 1;
        int uw = k1 == 'm', vw = k2 == 'm';
        adj[u * 2 + !uw].emplace_back(v * 2 + vw);
        adj[v * 2 + !vw].emplace_back(u * 2 + uw);
    }

    std::vector<int> stk;
    std::vector<bool> vis(n * 2);
    auto dfs = [&](auto &dfs, int from) -> bool {
        if (vis[from ^ 1])  
            return false;
        else if (vis[from])
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
        std::cout << "GOOD\n";
    } else {
        std::cout << "BAD\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test = 1;
    std::cin >> test;

    while (test --> 0) {
        Main();    
    }
}