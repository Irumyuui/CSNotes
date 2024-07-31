#include <iostream>
#include <vector>

using namespace std;

vector<int>fa;
vector<int>height;

int dfs(int v)
{
    if (height[v]){
        return height[v];
    }else{
        if (fa[v] != 0){
            height[v] = dfs(fa[v]) + 1;
        }else{
            height[v] = 1;
        }
        return height[v];
    }
}

int main()
{
    int n;
    cin >> n;
    fa = vector<int>(n + 1, 0);
    height = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++i)
    {
        int a, b;
        cin >> a >> b;
        fa[a] = fa[b] = i;
    }
    int maxheight = -1;
    for (int i = 1; i <= n; ++i)
    {
        maxheight = max(maxheight, dfs(i));
    }
    cout << maxheight;
    return 0;
}