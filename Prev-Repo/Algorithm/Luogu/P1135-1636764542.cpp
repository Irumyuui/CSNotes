#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>

using namespace std;

int n, sta, fend;
vector<int>elevitor;
vector<bool>vis;
vector<int>dist;

int bfs(int st)
{
    queue<int>q;
    q.push(st);
    int x = st;
    while (!q.empty())
    {
        x = q.front();
        q.pop();
        if (x == fend)
            return dist[x];
        int up, down;
        up = x + elevitor[x];
        down = x - elevitor[x];
        if (up > 0 && up <= n){
            if (!vis[up]){
                q.push(up);
                vis[up] = true;
                dist[up] = dist[x] + 1;
            }
        }
        if (down > 0 && down <= n){
            if (!vis[down]){
                q.push(down);
                vis[down] = true;
                dist[down] = dist[x] + 1;
            }
        }
    }
    return -1;
}

int main()
{
    cin >> n >> sta >> fend;
    dist = vector<int>(n + 1, 0);
    vis = vector<bool>(n + 1, false);
    elevitor = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> elevitor[i];
    }
    cout << bfs(sta);
    return 0;
}