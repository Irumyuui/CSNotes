#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

int n, m, a, b, w;
vector<vector<PII>>g;
vector<int>cnt, dist;
vector<bool>vis;

bool spfa(int sta){
    fill(dist.begin(), dist.end(), 0x7FFFFFFF);
    fill(cnt.begin(), cnt.end(), 0);
    fill(vis.begin(), vis.end(), false);
    queue<int>q;
    dist[sta] = 0;
    vis[sta] = true;
    q.push(sta);
    while (!q.empty()){
        int v = q.front();
        q.pop();
        vis[v] = false;
        for (auto it : g[v]){
            if (dist[it.first] > dist[v] + it.second){
                dist[it.first] = dist[v] + it.second;
                cnt[it.first] = cnt[v] + 1;
                if (cnt[it.first] >= n){
                    return false;
                }
                if (!vis[it.first]){
                    q.push(it.first);
                }
            }
        }
    }
    return true;
}

void solve(){
    cin >> n >> m;
    g = vector<vector<PII>>(n + 1, vector<PII>());
    cnt = dist = vector<int>(n + 1);
    vis = vector<bool>(n + 1);
    for (int i = 0; i < m; ++ i){
        cin >> a >> b >> w;
        if (w >= 0){
            g[a].push_back({b, w});
            g[b].push_back({a, w});
        }else{
            g[a].push_back({b, w});
        }
    }
    if (spfa(1) == false){
        cout << "YES" << endn;
    }else{
        cout << "NO" << endn;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t --){
        solve();
    }
    return 0;
}