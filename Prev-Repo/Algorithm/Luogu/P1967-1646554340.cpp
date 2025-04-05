#include <bits/stdc++.h>
using namespace std;
#define all(x) std::begin(x), std::end(x)
const int MAXN = 1e6 + 10;

int n, m, tot;
vector<int>g[MAXN];

inline void add(int u, int v) {
    g[u].push_back(v);
}

int dad[MAXN], W[MAXN];

int Find(int v) {
    if (dad[v] != -1)
        return dad[v] = Find(dad[v]);
    return v;
}

inline void prework() {
    struct Node {
        int u, v, w;
        bool operator < (Node &a) {
            return w > a.w;
        }
    };
    cin >> n >> m;
    vector<Node>edge(m);
    for (auto &[u, v, w] : edge) cin >> u >> v >> w;
    sort(all(edge));
    fill(all(dad), -1);
    tot = n;
    for (auto [u, v, w] : edge) {
        int du = Find(u), dv = Find(v);
        if (du == dv) 
            continue;
        tot ++;
        W[tot] = w;
        dad[du] = dad[dv] = tot;
        add(tot, du); add(tot, dv);
        add(du, tot); add(dv, tot);
    }   
}

int lg[MAXN], fa[MAXN][32], depth[MAXN];

void dfs(int now, int Dad) {
    fa[now][0] = Dad; depth[now] = depth[Dad] + 1;
    for (int i = 1; i <= lg[depth[now]]; ++ i) 
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (auto nex : g[now])
        if (nex != Dad) dfs(nex, now);
}

inline int LCA(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    while (depth[a] > depth[b]) 
        a = fa[a][lg[depth[a] - depth[b]]];
    if (a == b) return a;
    for (int i = lg[depth[a]]; i >= 0; -- i)
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i]; b = fa[b][i];
        }
    return fa[a][0];
}

inline void preLCA() {
    lg[0] = lg[1] = 0;
    lg[2] = 1;
    for (int i = 3; i <= tot; ++ i) 
        lg[i] = lg[i >> 1] + 1;
    // dfs(1, 0);
    for (int i = 1; i <= tot; ++ i) 
        if (Find(i) == i)
            dfs(i, 0);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    prework();
    preLCA();

    int t; cin >> t;
    while (t --) {
        int a, b; cin >> a >> b;
        if (Find(a) != Find(b)) {
            cout << -1 << '\n';
        } else {
            cout << W[LCA(a, b)] << '\n';
        }
    }

    return 0;
}