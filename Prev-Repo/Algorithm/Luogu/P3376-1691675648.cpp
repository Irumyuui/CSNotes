#include <bits/stdc++.h>

using i64 = int64_t;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 210, M = 2e5 + 10;
struct Edge {
    int to;
    i64 cap;
    int next;
    Edge(int to = {}, i64 cap = {}, int next = -1) : to(to), cap(cap), next(next) {

    }
};
std::vector<Edge> edge;
std::vector<int> head, cur, lv;

void init(int n, int siz) {
    edge.reserve(siz);
    head.assign(n, -1);
    cur.resize(n);
    lv.resize(n);
}

void add_edge(int from, int to, i64 cap) {
    edge.emplace_back(to, cap, head[from]); head[from] = int(edge.size()) - 1;
    edge.emplace_back(from, 0, head[to]); head[to] = int(edge.size()) - 1;
}

bool bfs(int s, int t) {
    std::ranges::fill(lv, -1);
    std::ranges::copy(head, cur.begin());
    std::queue<int> q;
    q.emplace(s);
    lv[s] = 0;
    while (!q.empty()) {
        int from = q.front();
        q.pop();
        for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
            auto [to, cap, __] = edge[ed];
            if (cap > 0 && lv[to] == -1) {
                lv[to] = lv[from] + 1;
                q.emplace(to);
            }
        }
    }
    return lv[t] != -1;
}

i64 dfs(int from, int t, i64 flow) {
    if (from == t) {
        return flow;
    }
    auto lesf = flow;
    for (int &ed = cur[from]; ed != -1 && lesf > 0; ed = edge[ed].next) {
        auto &&[to, cap, __] = edge[ed];
        if (cap > 0 && lv[to] == lv[from] + 1) {
            auto ret = dfs(to, t, std::min(lesf, cap));
            lesf -= ret;
            cap -= ret;
            edge[ed ^ 1].cap += ret;
        }
    }
    return flow - lesf;
}

i64 max_flow(int s, int t) {
    i64 flow = 0;
    while (bfs(s, t)) {
        flow += dfs(s, t, inf<i64>);
    }
    return flow;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m, s, t;
    std::cin >> n >> m >> s >> t;
    
    init(n, m * 2);

    s --; t --;
    for (int i = 0; i < m; i ++) {
        int from, to;
        i64 cap;
        std::cin >> from >> to >> cap;
        from --; to --;
        add_edge(from, to, cap);
    }

    std::cout << max_flow(s, t) << '\n';
}