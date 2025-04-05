#include <bits/stdc++.h>

std::vector< std::vector<int> > g;
std::vector<int> w;

int anss = 0;
std::vector<int> ans;
std::vector<bool> vis;

void dfs(int now, int fa, int sum, std::vector<int> & path) {
    path.push_back(now);
    sum += w[now];
    vis[now] = true;
    for (auto nex : g[now]) {
        if (nex != fa && !vis[nex])
            dfs(nex, now, sum, path);
    }
    if (anss < sum) {
        anss = sum;
        ans = path;
    }
    vis[now] = false;
    path.pop_back();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    g.assign(n + 1, std::vector<int>());
    w.assign(n + 1, 0);
    vis.assign(n + 1, false);
    for (int i = 1; i <= n; ++ i) {
        std::cin >> w[i];
    }
    for (int i = 1; i < n; ++ i) {
        for (int j = i + 1; j <= n; ++ j) {
            int x;
            std::cin >> x;
            if (x) {
                g[i].push_back(j);
                // g[j].push_back(i);
            }
        }
    }

    std::vector<int> tmp;
    for (int i = 1; i <= n; ++ i)
        dfs(i, 0, 0, tmp);
    for (auto it : ans) {
        std::cout << it << ' ';
    }
    std::cout << '\n' << anss;

    return 0;
}