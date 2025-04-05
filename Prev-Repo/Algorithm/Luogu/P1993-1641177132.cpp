#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

int n, m, x, a, b, w;
vector<vector<PII>>g;
vector<int>dis, cnt;
vector<bool>vis;

bool spfa(int sta){
    fill(dis.begin(), dis.end(), 0x7fffffff);
    fill(vis.begin(), vis.end(), false);
    fill(cnt.begin(), cnt.end(), 0);
    queue<int>q;
    q.push(sta);
    dis[sta] = 0;
    vis[sta] = 1;
    while (!q.empty()){
        int v = q.front();
        q.pop();
        vis[v] = 0;
        for (auto it : g[v]){
            if (dis[it.first] > dis[v] + it.second){
                dis[it.first] = dis[v] + it.second;
                cnt[it.first] = cnt[v] + 1;
                if (cnt[it.first] >= n + 1) return false;
                if (!vis[it.first]){
                    q.push(it.first);
                    vis[it.first] = 1;
                }
            }
        }
    }
    return true;
}

void solve(){
    cin >> n >> m;
    g = vector<vector<PII>>(n + 1, vector<PII>());
    vis = vector<bool>(n + 1);
    dis = cnt = vector<int>(n + 1);
    for (int i = 1; i <= n; ++ i){
        g[0].push_back({i, 0});
    }
    for (int i = 0; i < m; ++ i){
        cin >> x >> a >> b;
        if (x == 1){
            cin >> w;
            g[a].push_back({b, -w});
        }else if (x == 2){
            cin >> w;
            g[b].push_back({a, w});
        }else{
            g[b].push_back({a, 0});
            g[a].push_back({b, 0});
        }
    }
    if (spfa(0)){
        cout << "Yes" << endn;
    }else{
        cout << "No" << endn;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}