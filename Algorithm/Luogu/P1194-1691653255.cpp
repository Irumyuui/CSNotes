#include <bits/stdc++.h>
#include <execution>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int s, n;
    std::cin >> s >> n;

    std::vector<std::tuple<int,int,int>> edge;
    for (int i = 1; i <= n; i ++) {
        edge.emplace_back(s, i, 0);
    }
    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            int w;
            std::cin >> w;
            if (w > 0)
                edge.emplace_back(w, i, j);
        }
    }
    std::sort(std::execution::par_unseq, edge.begin(), edge.end());
       
    std::vector<int> dsu(n + 1, -1);
    auto Find = [&](auto &&Find, int x) -> int {
        return dsu[x] <= -1 ? x : dsu[x] = Find(Find, dsu[x]);
    };
    auto Merge = [&](int a, int b) -> bool {
        a = Find(Find, a); b = Find(Find, b);
        if (a == b) {
            return false;
        }
        dsu[a] = b;
        return true;
    };
    
    int ans = 0;
    for (auto [w, u, v] : edge) {
        if (Merge(u, v)) {
            ans += w;
        }
    }

    std::cout << ans << '\n';
}