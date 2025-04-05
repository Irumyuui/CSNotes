#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6 + 10;
vector<vector<int>>g;
int depth[MAXN], lg[MAXN], fa[MAXN][31];

void dfs(int now, int father) {
    fa[now][0] = father; depth[now] = depth[father] + 1;
    for (int i = 1; i <= lg[depth[now]]; ++ i)
        fa[now][i] = fa[fa[now][i - 1]][i - 1];
    for (auto nex : g[now])
        if (nex != father)
            dfs(nex, now);
}

int LCA(int a, int b) {
    if (depth[a] < depth[b])
        swap(a, b);
    while (depth[a] > depth[b])
        a = fa[a][lg[depth[a] - depth[b]]];
    if (a == b)
        return a;
    for (int i = lg[depth[a]]; i >= 0; -- i) {
        if (fa[a][i] != fa[b][i]) {
            a = fa[a][i];
            b = fa[b][i];
        }
    }
    return fa[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, root;
    cin >> n >> m >> root;
    g.assign(n + 1, vector<int>());
    for (int i = 1; i < n; ++ i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    lg[1] = 0, lg[2] = 1;
    for (int i = 3; i <= n; ++ i) {
        lg[i] = lg[i / 2] + 1;
    }
    dfs(root, 0);
    for (int i = 1; i <= m; ++ i) {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }

    return 0;
}