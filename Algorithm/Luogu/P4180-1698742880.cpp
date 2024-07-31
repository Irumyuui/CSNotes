#include <bits/stdc++.h>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max();

using i64 = int64_t;

constexpr int N = 5e5 + 10;
struct Info {
    i64 first, second;
    Info(i64 first = -inf<i64>, i64 second = -inf<i64>) : first(first), second(second) {}
    friend Info operator + (const Info &left, const Info &right) {
        auto tmp = std::array{left.first, left.second, right.first, right.second};
        std::ranges::sort(tmp, std::greater{});
        int last = 0;
        while (tmp[0] == tmp[last]) last ++;
        return Info{tmp[0], last < 4 ? tmp[last] : -inf<i64>};
    }
};
struct Node {
    Info val;  
} seg[N * 4];

void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void build(int l, int r, int id, const std::vector<int> &rnk, const std::vector<i64> &vw) {
    if (l == r) {
        seg[id].val = {vw[rnk[l]], -inf<i64>};
    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, rnk, vw);
        build(mid + 1, r, id * 2 + 1, rnk, vw);
        rise(id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}

void Main() {
    int n, m;
    std::cin >> n >> m;
    
    struct Edge {
        int u, v;
        i64 w;  
        constexpr Edge(int u = {}, int v = {}, i64 w = {})
            : u(u), v(v), w(w) {}
    };
    std::vector<Edge> edge;
    edge.reserve(m);
    for (int i = 0; i < m; i ++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        u --; v --;
        if (u != v) {
            edge.emplace_back(u, v, w);
        }
    }
    std::sort(edge.begin(), edge.end(), [](const auto &left, const auto &right) {
        return left.w < right.w;
    });
    
    struct DSU {
        std::vector<int> dad;
        DSU(int n) : dad(n, -1) {}
        int Find(int x) {
            if (dad[x] <= -1) {
                return x;
            }
            return dad[x] = Find(dad[x]);
        }
        bool MergeTo(int from, int to) {
            from = Find(from); to = Find(to);
            if (from == to) {
                return false;
            }
            dad[to] += dad[from];
            dad[from] = to;
            return true;
        }
    };
    
    DSU dsu(n);
    std::vector adj(n, std::vector<std::pair<int,i64>>{});
    std::vector<bool> choose(edge.size());
    i64 pre_ret = 0;
    for (int idx = 0; auto [u, v, w] : edge) {
        if (dsu.MergeTo(u, v)) {
            adj[u].emplace_back(v, w);
            adj[v].emplace_back(u, w);
            pre_ret += w;
            choose[idx] = true;
        }
        idx ++;
    }
    
    std::vector<int> dfn(n, -1), rnk(dfn), siz(dfn), son(dfn), top(dfn), fa(dfn), dep(dfn);
    std::vector<i64> ew_to_v(n, -inf<i64>);
    auto dfs1 = [&](auto &dfs, int from) -> void {
        siz[from] = 1;
        son[from] = -1;
        for (auto [to, w] : adj[from]) {
            if (dep[to] == -1) {
                dep[to] = dep[from] + 1;
                fa[to] = from;
                ew_to_v[to] = w;
                dfs(dfs, to);
                siz[from] += siz[to];
                if (son[from] == -1 || siz[to] > siz[son[from]]) {
                    son[from] = to;
                }
            }
        }
    };
    auto dfs2 = [&, stamp{0}](auto &dfs, int from, int link_top) mutable -> void {
        dfn[from] = stamp;
        rnk[stamp] = from;
        stamp ++;
        top[from] = link_top;
        if (son[from] == -1) {
            return;
        }
        dfs(dfs, son[from], link_top);
        for (auto [to, _] : adj[from])
            if (to != son[from] && to != fa[from])
                dfs(dfs, to, to);
    };
    dep[0] = 0;
    dfs1(dfs1, 0);
    dfs2(dfs2, 0, 0);
    
    build(0, n - 1, 1, rnk, ew_to_v);
    
    auto Query = [&](int a, int b) -> Info {
        Info ret{};
        while (top[a] != top[b]) {
            if (dep[top[a]] < dep[top[b]])
                std::swap(a, b);
            ret = ret + query(0, n - 1, 1, dfn[top[a]], dfn[a]);
            a = fa[top[a]];
        }
        if (dfn[a] > dfn[b]) {
            std::swap(a, b);
        }
        if (dfn[a] < dfn[b]) {
            ret = ret + query(0, n - 1, 1, dfn[a] + 1, dfn[b]);
        }
        return ret;
    };
    
    i64 ans = inf<i64>;
    for (int idx = 0; auto [u, v, w] : edge) {
        if (choose[idx ++]) {
            continue;
        }

        auto ret = Query(u, v);
        // std::cerr << u << ' ' << v << ' ' << ret.first << ' ' << ret.second << '\n';

        if (ret.first != w && ret.first != -inf<i64>) {
            ans = std::min(ans, pre_ret - ret.first + w);
        } else if (ret.second != -inf<i64>) {
            ans = std::min(ans, pre_ret - ret.second + w);
        }
    }
    // std::cout << pre_ret << '\n';
    std::cout << ans << '\n';
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    Main();
}