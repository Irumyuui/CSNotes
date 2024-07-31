#include <iostream>
#include <vector>

using namespace std;

typedef pair<int, bool> PIB;

vector<vector<PIB>>g;
vector<int>dad;

int FIND(int v)
{
    if (dad[v] != v){
        dad[v] = FIND(dad[v]);
    }
    return dad[v];
}

void Union(int a, int b)
{
    a = FIND(a);
    b = FIND(b);
    if (a != b){
        dad[a] = b;
    }
}

int main()
{
    int n, m;
    cin >> n >> m;
    g = vector<vector<PIB>>(n + 1, vector<PIB>());
    dad = vector<int>(n + 1);
    for (int i = 0; i < dad.size(); ++ i)
    {
        dad[i] = i;
    }
    while (m --)
    {
        int a, b, fe;
        char f;
        getchar();
        cin >> f >> a >> b;
        if (f == 'E'){
            fe = 0;
        }else{
            fe = 1;
        }
        g[a].push_back({b, fe});
        g[b].push_back({a, fe});
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (auto it : g[i])
        {
            if (it.second == 1){
                Union(i, it.first);
            }else{
                for (auto it2 : g[it.first])
                {
                    if (it2.second == 0){
                        Union(i, it2.first);
                    }
                }
            }
        }
    }
    int res = 0;
    for (int i = 1; i <= n; ++ i)
    {
        if (dad[i] == i){
            res ++;
        }
    }
    cout << res;
    return 0;
}
