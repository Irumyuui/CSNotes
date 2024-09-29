# SPFA

```c++
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = std::int64_t;

void Main() {
    int n, m, s;
    std::cin >> n >> m >> s;
    s--;

    std::vector adj(n, std::vector<std::pair<int, i64>>{});
    for (int i = 0; i < m; i++) {
        int from, to, w;
        std::cin >> from >> to >> w;
        from--;
        to--;
        adj[from].emplace_back(to, w);
    }

    std::queue<int> q;
    std::vector<bool> inq(n);
    std::vector<i64> dis(n, inf<i64>);
    q.emplace(s);
    dis[s] = 0;
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        inq[from] = false;
        for (auto [to, ew] : adj[from]) {
            if (dis[to] > dis[from] + ew) {
                dis[to] = dis[from] + ew;
                if (!inq[to]) {
                    q.emplace(to);
                    inq[to] = true;
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (dis[i] == inf<i64>) {
            std::cout << (static_cast<i64>(1) << 31) - 1;
        } else {
            std::cout << dis[i];
        }
        std::cout << " \n"[i + 1 == n];
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Main();
}
```