#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;

int n, m;
vector<vector<PII>>g;
vector<vector<PII>>rg;
vector<int>dist, rdist;
vector<bool>vis;

void dijkstar(int sta, vector<vector<PII>> &g, vector<int>&dist){
    priority_queue<PII, vector<PII>, greater<PII>>q;
    q.push({(dist[sta] = 0), sta});
    while (!q.empty()){
        PII p = q.top();
        q.pop();
        if (vis[p.second]){
            continue;
        }
        vis[p.second] = true;
        for (auto it : g[p.second]){
            if (dist[p.second] + it.second < dist[it.first]){
                dist[it.first] = dist[p.second] + it.second;
                q.push({dist[it.first], it.first});
            }
        }
    }
    return;
}

void solve(){
    cin >> n >> m;
    rg = g = vector<vector<PII>>(n + 1, vector<PII>());
    dist = rdist = vector<int>(n + 1, INFI);
    vis = vector<bool>(n + 1, false);
    for (int i = 0; i < m; ++ i){
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
        rg[b].push_back({a, w});
    }
    vector<int>path;
    dijkstar(1, g, dist);
    fill(vis.begin(), vis.end(), false);
    dijkstar(1, rg, rdist);
    int ans = 0;
    for (int i = 2; i <= n; ++ i){
        ans += (dist[i] + rdist[i]);
    }
    cout << ans;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}