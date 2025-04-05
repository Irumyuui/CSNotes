#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>
#include <cstdio>
#include <queue>
#include <set>
#include <map>

using namespace std;

class edge
{
    public:
        int a, b, w;
        edge(const int &a, const int &b, const int &w)
        {
            this->a = a;
            this->b = b;
            this->w = w;
        }
};

bool operator>(const edge &a, const edge &b)
{
    return a.w > b.w;
}

typedef pair<int, int> PII;

vector< vector<PII> > g;
vector<int>dad;

int Find(int v)
{
    if (dad[v] != v){
        dad[v] = Find(dad[v]);
    }
    return dad[v];
}

bool isCycle(int a, int b)
{
    a = Find(a);
    b = Find(b);
    if (a == b){
        return true;
    }else{
        return false;
    }
}

void Union(int a, int b)
{
    a = Find(a);
    b = Find(b);
    dad[a] = b;
}

vector<edge> kur()
{
    priority_queue<edge, vector<edge>, greater<edge> >q;
    for (int i = 1; i < g.size(); ++ i)
    {
        for (auto it : g[i])
        {
            q.push(edge(i, it.first, it.second));
        }
    }
    vector<edge>tree;
    while (!q.empty() && tree.size() < g.size() - 2)
    {
        edge e = q.top();
        q.pop();
        if (!isCycle(e.a, e.b)){
            Union(e.a, e.b);
            tree.push_back(e);
        }
    }
    return tree;
}

int main()
{
    int n, m;
    cin >> n >> m;
    g = vector<vector<PII> >(n + 1, vector<PII>());
    dad = vector<int>(n + 1);
    for (int i = 0; i <= n; ++ i)
    {
        dad[i] = i;
    }
    for (int i = 0; i < m; ++ i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back({b, w});
    }
    vector<edge>tree = kur();
    if (tree.size() < g.size() - 2){
        cout << "orz" << endl;
    }else{
        int res = 0;
        for (auto it : tree)
        {
            res += it.w;
        }
        cout << res << endl;
    }
    return 0;
}