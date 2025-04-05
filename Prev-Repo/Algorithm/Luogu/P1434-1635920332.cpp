#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

int r_, c_;
vector< vector<PII> >g;

int hd[4] = {-1, 0, 1, 0};
int lr[4] = {0, -1, 0, 1};

int dfs(int r, int c)
{
    if (g[r][c].second != -1){
        return g[r][c].second;
    }else{
        int res = 1;
        for (int i = 0; i < 4; ++ i)
        {
            int x = r + hd[i];
            int y = c + lr[i];
            if ((x >= 0 && x < r_) && (y >= 0 && y < c_) && g[x][y].first < g[r][c].first){
                res = max(res, dfs(x, y) + 1);
            }
        }
        g[r][c].second = res;
        return g[r][c].second;
    }
}

int main()
{
    cin >> r_ >> c_;
    g = vector< vector<PII> >(r_, vector<PII>(c_, {0, -1}));
    for (int i = 0; i < r_; ++ i)
    {
        for (int j = 0; j < c_; ++ j)
        {
            cin >> g[i][j].first;
        }
    }
    int res = -1;
    for (int i = 0; i < r_; ++ i)
    {
        for (int j = 0; j < c_; ++ j)
        {
            res = max(res, dfs(i, j));
        }
    }
    cout << res;
    return 0;
}