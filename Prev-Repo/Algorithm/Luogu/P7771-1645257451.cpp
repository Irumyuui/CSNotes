#include <bits/stdc++.h>
#define all(x) begin(x), end(x)

std::vector< std::vector<int> >g;
std::vector<int>ru, chu, nex;
std::stack<int>ans;

void dfs(int u) {
    for (int i = nex[u]; i < g[u].size(); i = nex[u]) {
        nex[u] = i + 1;
        dfs(g[u][i]);
    }
    
    ans.push(u);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    g.assign(n + 1, std::vector<int>());
    ru.assign(n + 1, 0);
    chu.assign(n + 1, 0);
    nex.assign(n + 1, 0);

    for (int i = 1; i <= m; ++ i) {
        int u, v;
        std::cin >> u >> v;
        g[u].push_back(v);
        ru[v] ++;
        chu[u] ++;
    }

    bool equaldeg = true;    
    int in = 0, out = 0, sta = 1;

    for (int i = 1; i <= n; ++ i) {
        if (ru[i] != chu[i]) {
            equaldeg = false;
        }
        int t = ru[i] - chu[i];
        if (t == 1) {
            in ++;
        }
        if (t == -1) {
            sta = i;
            out ++;
        }
    }

    if (equaldeg == false && !(in == out && in == 1)) {
        std::cout << "No";
        return 0;
    }

    for (auto &it : g) {
        sort(all(it));
    }

    dfs(sta);

    while (!ans.empty()) {
        std::cout << ans.top() << ' ';
        ans.pop();
    }

    return 0;
}