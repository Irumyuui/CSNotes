#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int, int> PII;

const int INF = 0x7FFFFFFF;

vector< vector<PII> >g;
vector<int>dist;
vector<bool>found;

void dijkstra(int startv)
{
    priority_queue<PII, vector<PII>, greater<PII> >q;
    for (int i = 1; i < dist.size(); ++i)
    {
        if (i != startv){
            dist[i] = INF;
        }else{
            dist[i] = 0;
            q.push({dist[i], i});
        }
    }
    int v;
    while (!q.empty())
    {
        v = q.top().second;
        q.pop();
        if (!found[v]){
            found[v] = true;
            for (auto it : g[v])
            {
                if (dist[v] + it.second < dist[it.first]){
                    dist[it.first] = dist[v] + it.second;
                    q.push({dist[it.first], it.first});
                }
            }
        }
    }
}

int main()
{
    int n, m, s;
    scanf("%d%d%d", &n, &m, &s);
    g = vector< vector<PII> >(n + 1, vector<PII>());
    dist = vector<int>(n + 1, INF);
    found = vector<bool>(n + 1, false);
    for (int i = 0; i < m; ++i)
    {
        int a, b, w;
        scanf("%d%d%d", &a, &b, &w);
        g[a].push_back({b, w});
    }
    dijkstra(s);
    int space = 0;
    for (int i = 1; i <= n; ++i)
    {
        if (space == 1){
            printf(" ");
        }else{
            space = 1;
        }
        printf("%d", dist[i]);
    }
    return 0;
}