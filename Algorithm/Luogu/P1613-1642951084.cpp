#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)

typedef long long LL;

const int LEN = 64;

LL dist[LEN][LEN];
bool g[LEN][LEN][LEN];
int n, m;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    fill(dist[0], dist[0] + LEN * LEN, 1ll << 45);
    fill(g[0][0], g[0][0] + LEN * LEN * LEN, false);
    cin >> n >> m;
    for (int i = 1; i <= m; ++ i)
    {
        int u, v;
        cin >> u >> v;
        g[u][v][0] = true;
        dist[u][v] = 1;
    }
    for (int b = 1; b <= LEN; ++ b)
    {
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= n; ++ j)
            {
                for (int k = 1; k <= n; ++ k)
                {
                    if (g[i][j][b - 1] && g[j][k][b - 1]){
                        g[i][k][b] = true;
                        dist[i][k] = 1;
                    }
                }
            }
        }
    }
    for (int k = 1; k <= n; ++ k)
    {
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= n; ++ j)
            {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cout << dist[1][n];
    return 0;
}