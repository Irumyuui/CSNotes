# Dinic

```c++
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = std::int64_t;

struct Edge {
    int to, cap, next;
};
std::vector<Edge> edges;
std::vector<int> head, cur, level;

void init(int n, int m) {
    edges.reserve(m);
    head.assign(n, -1);
    cur.resize(n);
    level.resize(n);
}

void add_edges(int from, int to, int cap) {
    edges.emplace_back(to, cap, head[from]);
    head[from] = edges.size() - 1;

    edges.emplace_back(from, 0, head[to]);
    head[to] = edges.size() - 1;
}

bool bfs(int s, int t) {
    std::ranges::fill(level, -1);
    std::copy(head.begin(), head.end(), cur.begin());
    level[s] = 0;

    std::queue<int> q;
    q.emplace(s);
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int eidx = head[from]; ~eidx; eidx = edges[eidx].next) {
            auto [to, cap, _] = edges[eidx];
            if (cap > 0 && level[to] == -1) {
                level[to] = level[from] + 1;
                q.emplace(to);
            }
        }
    }

    return level[t] != -1;
}

int dfs(int from, int t, int tot_flow = inf<int>) {
    if (from == t) {
        return tot_flow;
    }
    auto less_flow = tot_flow;
    for (int &eidx = cur[from]; ~eidx && less_flow > 0;
         eidx = edges[eidx].next) {
        int to = edges[eidx].to, cap = edges[eidx].cap;
        if (cap > 0 && level[to] == level[from] + 1) {
            auto ret_flow = dfs(to, t, std::min(tot_flow, cap));
            less_flow -= ret_flow;
            edges[eidx].cap -= ret_flow;
            edges[eidx ^ 1].cap += ret_flow;
        }
    }
    return tot_flow - less_flow;
}

int dinic(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        flow += dfs(s, t);
    }
    return flow;
}

void Main() {
    int n, m, ecnt;
    std::cin >> n >> m >> ecnt;

    init(n + m + 2, int(1e6 + 10));
    int s = n + m, t = n + m + 1;

    for (int i = 0; i < n; i++) {
        add_edges(s, i, 1);
    }
    for (int i = 0; i < m; i++) {
        add_edges(i + n, t, 1);
    }
    for (int i = 0; i < ecnt; i++) {
        int u, v;
        std::cin >> u >> v;
        u--;
        v = v - 1 + n;
        add_edges(u, v, 1);
    }

    std::cout << dinic(s, t) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Main();
}
```