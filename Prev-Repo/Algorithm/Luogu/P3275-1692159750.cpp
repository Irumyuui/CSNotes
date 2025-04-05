#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

LL n, a, b, x, ans, k;
vector<vector<PLL>>g;
vector<LL>cnt, dist;
vector<bool>vis;

bool SPFA(){
    fill(dist.begin(), dist.end(), -0x7ffffffff);
    vis[0] = true;
    dist[0] = 0;
    queue<int>q;
    q.push(0);
    while (!q.empty()){
        int v = q.front();
        q.pop();
        vis[v] = false;
        for (auto it : g[v]){
            if (dist[it.first] < dist[v] + it.second){
                dist[it.first] = dist[v] + it.second;
                if ((cnt[it.first] = cnt[v] + 1) >= n + 1){
                    return false;
                }
                if (!vis[it.first]){
                    q.push(it.first);
                    vis[it.first] = true;
                }
            }
        }
    }
    return true;
}

void solve(){
    cin >> n >> k;
    g = vector<vector<PLL>>(n + 1, vector<PLL>());
    cnt = dist = vector<LL>(n + 1, 0);
    vis = vector<bool>(n + 1, false);
    for (int i = 1; i <= n; ++ i){
        g[0].push_back({i, 1});
    }
    while (k --){
        cin >> x >> a >> b;
        if (x == 1){
            g[a].push_back({b, 0});
            g[b].push_back({a, 0});
        }else if (x == 2){
            if (a == b){
                cout << -1;
                return;
            }
            g[a].push_back({b, 1});
        }else if (x == 3){
            g[b].push_back({a, 0});
        }else if (x == 4){
            if (a == b){
                cout << -1;
                return;
            }
            g[b].push_back({a, 1});
        }else if (x == 5){
            g[a].push_back({b, 0});
        }
    }
    if (SPFA()){
        for (int i = 1; i <= n; ++ i){
            ans += dist[i];
        }
        cout << ans;
    }else{
        cout << -1;
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