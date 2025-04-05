#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, int> PII;

int r_, c_;
vector< vector<PII> >g;

int dfs(int r, int c)
{
    if (r < 0 || c < 0 || r >= r_ || c >= c_){
        return 0;
    }else if (g[r][c].second != -1){
        return g[r][c].second;
    }else{
        int res = 0;
        if (r > 0 && g[r][c].first > g[r - 1][c].first){
            res = max(res, dfs(r - 1, c));
        }
        if (r < r_ - 1 && g[r][c].first > g[r + 1][c].first){
            res = max(res, dfs(r + 1, c));
        }
        if (c > 0 && g[r][c].first > g[r][c - 1].first){
            res = max(res, dfs(r, c - 1));
        }
        if (c < c_ - 1 && g[r][c].first > g[r][c + 1].first){
            res = max(res, dfs(r, c + 1));
        }
        return (g[r][c].second = res + 1);
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