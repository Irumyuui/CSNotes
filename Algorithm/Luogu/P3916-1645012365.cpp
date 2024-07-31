#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
using ll = long long;

int n, m;

vector< vector< int > >g;
vector<int>ans;
vector<bool>vis;

inline void add(int &u, int &v) {
    g[u].push_back(v);
}

void bfs(int sta) {
    vis[sta] = true;

    queue<int>q;
    q.push(sta);

    while (!q.empty()){
        int u = q.front();
        q.pop();

        for (const auto &v : g[u]){
            if (ans[v] < sta){
                ans[v] = sta;

                if (!vis[v]){
                    vis[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    cin >> n >> m;

    g.assign(n + 1, vector<int>());
    ans.assign(n + 1, 0);
    vis.assign(n + 1, false);

    iota(all(ans), 0);

    for (int i = 1; i <= m; ++ i) {
        int u, v;
        cin >> u >> v;
        add(v, u);
    }

    for (int i = n; i >= 1; -- i){
        bfs(i);
        fill(all(vis), false);
    }

    for (int i = 1; i <= n; ++ i){
        cout << ans[i] << ' ';
    }

    return 0;
}