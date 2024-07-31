#include <iostream>
#include <vector>

using namespace std;

struct work{
    int time;
    vector<int>nw;
};

vector<work>g;
vector<int>dfsv;

int dfs(int v)
{
    if (dfsv[v]) return dfsv[v];
    for (int i=0;i<g[v].nw.size();++i)
    {
        dfsv[v] = max(dfsv[v], dfs(g[v].nw[i]));
    }
    dfsv[v] += g[v].time;
    return dfsv[v];
}

int main()
{
    int n;
    cin >> n;
    g=vector<work>(n+1);
    dfsv=vector<int>(n+1, 0);
    for (int i=0;i<n;++i)
    {
        int x;
        cin >> x;
        cin >> g[x].time;
        int w;
        while (cin >> w && w != 0)
        {
            g[x].nw.push_back(w);
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++i)
    {
        res = max(res, dfs(i));
    }
    cout << res;
    return 0;
}