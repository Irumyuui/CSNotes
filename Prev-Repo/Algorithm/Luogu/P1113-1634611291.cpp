#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>>g;
vector<int>vtime;
vector<int>found;

int sdfs(int v)
{
    if (found[v]){
        return found[v];
    }
    for (int i = 0; i < g[v].size(); ++i)
    {
        found[v] = max(found[v], sdfs(g[v][i]));
    }
    found[v] += vtime[v];
    return found[v];
}

int main()
{
    int v;
    cin >> v;
    g = vector<vector<int>>(v + 1, vector<int>());
    vtime = vector<int>(v + 1);
    found = vector<int>(v + 1, 0);
    for (int i = 1; i <= v; ++i)
    {
        int x;
        cin >> x;
        cin >> vtime[x];
        int y;
        while (cin >> y && y > 0)
        {
            g[x].push_back(y);
        }
    }
    int maxn = 0;
    for (int i = 1; i <= v; ++i)
    {
        maxn = max(maxn, sdfs(i));
    }
    cout << maxn;
    return 0;
}