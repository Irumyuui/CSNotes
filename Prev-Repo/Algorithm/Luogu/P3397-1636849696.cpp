#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

vector<vector<int>>floot;

int main()
{
    int n, m;
    cin >> n >> m;
    floot = vector<vector<int>>(n + 1, vector<int>(n + 1, 0));
    while (m --)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i = x1; i <= x2 && i <= n; ++ i)
        {
            for (int j = y1; j <= y2 && j <= n; ++ j)
            {
                floot[i][j] ++;
            }
        }
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= n; ++ j)
        {
            cout << floot[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}