#include <bits/stdc++.h>
using namespace std;
#define all(x) std::begin(x), std::end(x)

const int MAXN = 1e6 + 10;
int n, m;

vector<int>g[MAXN];
inline void pushedge(int u, int v) {
    g[u].push_back(v);
}

int tot = 0;
int W[MAXN] = {};

struct Dset {
    vector<int>dad;
    void inti(int size) {
        dad.assign(size + 1, -1);
    }
    int &operator [] (int i) {
        return dad[i];
    }
    int Find(int v) {
        if (dad[v] != - 1) {
            return dad[v] = Find(dad[v]);
        }
        return v;
    }
    bool Union(int a, int b) {
        a = Find(a);
        b = Find(b);
        if (a == b) 
            return false;
        dad[a] = b;
        return true;
    }
};

struct LCA {
    vector<vector<int>>fa;  
    vector<int>lg, depth;
    void inti(int size) {
        fa.assign(size + 1, vector<int>(32, 0));
        lg.assign(size + 1, 0);
        depth.assign(size + 1, 0);
        lg[2] = 1;
        for (int i = 3; i < lg.size(); ++ i) {
            lg[i] = lg[i >> 1] + 1;
        }
    }
    void dfs(int now, int dad) {
        fa[now][0] = dad;
        depth[now] = depth[dad] + 1;
        for (int i = 1; i <= lg[depth[now]]; ++ i) {
            fa[now][i] = fa[fa[now][i - 1]][i - 1];
        }
        for (auto nex : g[now]) {
            if (dad != nex) {
                dfs(nex, now);
            }
        }
    }
    int lca(int a, int b) {
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
                a = fa[a][i];
                b = fa[b][i];
            }
        }
        return fa[a][0];
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    struct Node {
        int u, v, w;
        bool operator < (const Node &a) const {
            return w > a.w;
        }
    };
    vector<Node>ed(m);
    for (auto &[u, v, w] : ed) {
        cin >> u >> v >> w;
    }
    sort(all(ed));

    Dset dset;
    dset.inti(n + m + 1);
    tot = n;
    for (const auto [u, v, w] : ed) {
        int du = dset.Find(u), dv = dset.Find(v);
        if (du != dv) {
            tot ++;
            dset[du] = dset[dv] = tot;
            W[tot] = w;
            pushedge(tot, du);
            pushedge(tot, dv);
            pushedge(du, tot);
            pushedge(dv, tot);
        }
    }

    LCA lca;
    lca.inti(tot + 1);
    for (int i = 1; i <= tot; ++ i) {
        if (dset.Find(i) == i) {
            lca.dfs(i, 0);
        }
    }
    
    int t;
    cin >> t;
    while (t --) {
        int a, b;
        cin >> a >> b;
        if (dset.Find(a) != dset.Find(b)) {
            cout << -1 << '\n';
        } else {
            cout << W[lca.lca(a, b)] << '\n';
        }
    }


    return 0;
}