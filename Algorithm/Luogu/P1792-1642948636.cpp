#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)

const int LEN = 2e5 + 10;

struct node
{
    int cost, lc, rc;
}lis[LEN];

bool vis[LEN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    if ((m << 1) > n){
        cout << "Error!";
        return 0;
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>>q;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> lis[i].cost;
        lis[i].lc = i - 1;
        lis[i].rc = i + 1;
        q.push({lis[i].cost, i});
    }
    lis[1].lc = n;
    lis[n].rc = 1;
    fill(all(vis), false);
    int ans = 0;
    for (int i = 1; i <= m; ++ i)
    {
        while (vis[q.top().second])
        {
            q.pop();
        }
        pair<int, int> p = q.top();
        q.pop();
        ans += p.first;
        vis[lis[p.second].lc] = vis[lis[p.second].rc] = 1;
        lis[p.second].cost = lis[lis[p.second].lc].cost + lis[lis[p.second].rc].cost - lis[p.second].cost;
        lis[p.second].lc = lis[lis[p.second].lc].lc;
        lis[lis[p.second].lc].rc = p.second;
        lis[p.second].rc = lis[lis[p.second].rc].rc;
        lis[lis[p.second].rc].lc = p.second;
        q.push({lis[p.second].cost, p.second});
    }
    cout << ans;
    return 0;
}