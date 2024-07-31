#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int> > >g;
int dist[115], cnt[115];
bool vis[115];
int n;

void solve()
{
    cin >> n;
    g = vector<vector<pair<int, int> > >(n + 2, vector<pair<int, int> >());
    fill(dist, dist + 115, -(1 << 30));
    fill(vis, vis + 115, false);
    fill(cnt, cnt + 115, 0);
    int m;
    cin >> m;
    int a, b, w;
    for (int i = 0; i <= n; ++ i)
    {
        g[n + 1].push_back({i, 0});
    }
    while (m --)
    {
        cin >> a >> b >> w;
        g[a - 1].push_back({b, -w});
        g[b].push_back({a - 1, w});
    }
    queue<int>q;
    q.push(n + 1);
    dist[n + 1] = 0;
    while (q.size())
    {
        int v = q.front();
        q.pop();
        vis[v] = false;
        for (auto it : g[v])
        {
            if (dist[it.first] < dist[v] + it.second){
                dist[it.first] = dist[v] + it.second;
                cnt[it.first] = cnt[v] + 1;
                if (cnt[it.first] >= n + 1){
                    cout << "false" << '\n';
                    return;
                }
                if (!vis[it.first]){
                    q.push(it.first);
                    vis[it.first] = true;
                }
            }
        }
    }
    cout << "true" << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test;
    cin >> test;
    while (test --)
    {
        solve();
    }
    return 0;
}