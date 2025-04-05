#include <bits/stdc++.h>
using namespace std;
#define all(x) std::begin(x), std::end(x)

const int MAXN = 1e6 + 10;
int n, m;
int dad[MAXN];
int tot = 0;

vector<int>g[MAXN];
int W[MAXN];  // ->v 's W

inline void add(int u, int v) {
    g[u].push_back(v);
}

int Find(int v) {
    if (dad[v] != -1) {
        return dad[v] = Find(dad[v]);
    }
    return v;
}
// inline bool/


inline void pre() {
    cin >> n >> m;
    struct Node {
        int u, v, w;  
    };
    vector<Node>de(m);
    for (auto &[u, v, w] : de) {
        cin >> u >> v >> w;
    }
    sort(all(de), [](const Node &a, const Node &b) {
        return a.w < b.w;
    });
    // vector<Node>ed;
    tot = n;
    fill(all(dad), -1);
    for (auto [u, v, w] : de) {
        // if (Union(it.u, it.v)) {
        u = Find(u); v = Find(v);
        if (u == v)
            continue;
        tot ++;
        dad[u] = dad[v] = tot;
        W[tot] = w;
        add(tot, u);
        add(tot, v);
        add(u, tot);
        add(v, tot);
    }

    
}

int lg[MAXN], fa[MAXN][31], depth[MAXN];

void dfs(int now, int da) {
    fa[now][0] = da;
    depth[now] = depth[da] + 1;
    for (int i = 1; i <= lg[depth[now]]; ++ i) {
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    }
    for (int nex : g[now]) {
        if (nex != da) {
            dfs(nex, now);
        }
    }
}

inline int LCA(int a, int b) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }
    while (depth[a] > depth[b]) {
        a = fa[a][lg[depth[a] - depth[b]]];
    }
    if (a == b) {
        return a;
    }
    for (int i = lg[depth[a]]; i >= 0; -- i) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i]; b = fa[b][i];
        }
    }
    return fa[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pre();

    lg[0] = lg[1] = 0;
    lg[2] = 1;
    for (int i = 3; i <= tot; ++ i) {
        lg[i] = lg[i >> 1] + 1;
    }    
    for (int i = 1; i <= tot; ++ i) {
        if (i == Find(i)) {
            dfs(i, 0);
        }
    }

    int t;
    cin >> t;
    while (t --) {
        int a, b;
        cin >> a >> b;
        if (Find(a) != Find(b)) {
            cout << "impossible" << '\n';
        } else {
            cout << W[LCA(a, b)] << '\n';
        }
    }

    return 0;
}