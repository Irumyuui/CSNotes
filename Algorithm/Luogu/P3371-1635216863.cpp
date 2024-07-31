#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 99999999;

struct edge{
    int v, weight;
    edge(const int &v, const int &weight)
    {
        this->v = v;
        this->weight = weight;
    }
    bool operator < (const edge &a) const
    {
        return this->weight < a.weight;
    }
    bool operator > (const edge &a) const{
        return this->weight > a.weight;
    }
};

vector< vector<edge> >g;
vector<int>dist;
vector<bool>found;

void dij(int alpha)
{
    dist[alpha] = 0;
    priority_queue<edge, vector<edge>, greater<edge> >q;
    q.push(edge(alpha, dist[alpha]));
    while (!q.empty())
    {
        edge v = q.top();
        q.pop();
        found[v.v] = true;
        for (auto it : g[v.v])
        {
            if (!found[it.v]){
                if (dist[v.v] + it.weight < dist[it.v]){
                    dist[it.v] = dist[v.v] + it.weight;
                    q.push(edge(it.v, dist[it.v]));
                }
            }
        }
    }
}

int main()
{
    int n, m, s;
    cin >> n >> m >> s;
    g = vector< vector<edge> >(n + 1, vector<edge>());
    dist = vector<int>(n + 1, INF);
    found = vector<bool>(n + 1, false);
    for (int i = 0; i < m; ++i)
    {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].push_back(edge(b, w));
    }
    dij(s);
    int space = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (space == 1){
            cout << ' ';
        }else{
            space = 1;
        }
        if (dist[i] == INF){
            cout << 0x7FFFFFFF;
        }else{
            cout << dist[i];
        }
    }
    return 0;
}