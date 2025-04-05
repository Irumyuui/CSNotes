#include <iostream>
#include <vector>

using namespace std;

int n;
vector<bool>nx, ny, nxy, nyx;
vector<vector<int>>res;

vector<int>v;
void dfs(int y)
{
    if (y > n){
        res.push_back(v);
        return;
    }
    for (int x = 1; x <= n; ++ x)
    {
        if (!nx[x] && !ny[y] && !nxy[x + y] && !nyx[x - y + n]){
            nx[x] = ny[y] = nxy[x + y] = nyx[x - y + n] = true;
            v[y] = x;
            dfs(y + 1);
            nx[x] = ny[y] = nxy[x + y] = nyx[x - y + n] = false;
        }
    }
}

int main()
{
    cin >> n;
    nx = ny = vector<bool>(n + 1, false);
    v = vector<int>(n + 1, 0);
    nxy = nyx = vector<bool>((n + 1) * (n + 1), false);
    dfs(1);
    for (int i = 0; i < 3 && i < res.size(); ++ i)
    {
        for (int j = 1; j < res[i].size(); ++ j)
        {
            cout << res[i][j] << ' ';
        }
        cout << endl;
    }
    cout << res.size() << endl;
    return 0;
}