#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<vector<int>>g;
vector<int>dfsv;
vector<int>Path;

void DFS(int v)
{
    dfsv[v] = 1;
    Path.push_back(v);
    for (int i = 0; i < g[v].size(); ++i)
    {
        if (!dfsv[g[v][i]]){
            DFS(g[v][i]);
        }
    }
}

void BFS(int v)
{
    queue<int>q;
    q.push(v);
    while (q.size())
    {
        int x = q.front();
        q.pop();
        dfsv[x] = 1;
        Path.push_back(x);
        for (auto it : g[x])
        {
            if (!dfsv[it]){
                dfsv[it] = 1;
                q.push(it);
            }
        }
    }
    
}

int main()
{
    int v, e;
    cin >> v >> e;
    g = vector<vector<int>>(v + 1, vector<int>());
    dfsv = vector<int>(v + 1, 0);
    for (int i = 0; i < e; ++i)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= v; ++i)
    {
        sort(g[i].begin(), g[i].end());
    }
    DFS(1);
    int space = 0;
    for (auto it : Path)
    {
        if (space == 1){
            cout << " ";
        }else{
            space = 1;
        }
        cout << it;
    }
    cout << endl;
    fill(dfsv.begin(), dfsv.end(), 0);
    Path.clear();
    space = 0;
    BFS(1);
    for (auto it : Path)
    {
        if (space == 1){
            cout << " ";
        }else{
            space = 1;
        }
        cout << it;
    }
    cout << endl;
    return 0;
}