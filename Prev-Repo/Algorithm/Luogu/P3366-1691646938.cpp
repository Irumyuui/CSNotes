#include <bits/stdc++.h>
#include <execution>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::tuple<int,int,int>> edge(m);
    for (auto &[w, u, v] : edge) {
        std::cin >> u >> v >> w;
        u --; v --;
    }
    std::sort(std::execution::par_unseq, edge.begin(), edge.end());

    std::vector<int> dsu(n, -1);
    auto Find = [&](auto &&Find, int x) -> int {    
        return dsu[x] <= -1 ? x : dsu[x] = Find(Find, dsu[x]);
    };
    auto Merge = [&](int a, int b) -> bool {
        a = Find(Find, a); b = Find(Find, b);
        if (a == b) {
            return false;
        }
        dsu[b] = a;
        return true;
    };
    
    int cnt = 0;
    i64 ans = 0;
    for (auto [w, u, v] : edge) {
        if (Merge(u, v)) {
            cnt ++;
            ans += w;
            if (cnt == n - 1) {
                break;
            }
        }     
    }

    if (cnt == n - 1) {
        std::cout << ans << '\n';
    } else {
        std::cout << "orz\n";
    }
}