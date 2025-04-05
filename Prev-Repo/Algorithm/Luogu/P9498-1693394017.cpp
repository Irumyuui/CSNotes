#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <ranges>

using i64 = int64_t;

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

    std::vector<int> dep(n, -1);
    auto dfs = [&](auto &self, int from) -> void {
        for (auto to : adj[from]) {
            if (dep[to] == -1) {
                dep[to] = dep[from] + 1;
                self(self, to);
            }
        }
    };
    dep[0] = 1;
    dfs(dfs, 0);

    i64 tot = std::reduce(dep.cbegin(), dep.cend(), (i64)0);

    if (tot % 2 != 0) {
        std::cout << -1 << '\n';
        return 0;
    }

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::ranges::sort(idx, [&](int a, int b) {
        return dep[a] < dep[b];
    });

    // std::cerr << tot << '\n';

    i64 tmp = tot / 2;
    std::vector<int> col(n);
    for (int i = n - 1; i >= 0; i --) {
        if (tmp >= dep[idx[i]]) {
            tmp -= dep[idx[i]];
            col[idx[i]] = 1;
        }
    }
    // std::cerr << tmp << '\n';
    // for (int i = 0; i < n; i ++) {
    //     std::cerr << dep[i] << " \n"[i + 1 == n];
    // }

    for (int i : col) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}