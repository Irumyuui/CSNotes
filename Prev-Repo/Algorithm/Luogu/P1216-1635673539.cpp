// #include <bits\stdc++.h>
#include <iostream>
#include <vector>

using namespace std;

#define debug(x) cerr << "DEBUG " << #x << ": " << x << endl;

typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

const int INF = 0x7FFFFFFF;

int n;
LL res;
vector< vector<int> >g;
vector< vector<int> >arr;
int dfs(int floot, int i)
{
    if (floot == n){
        return g[floot][i];
    }else if (arr[floot][i] != -1){
        return arr[floot][i];
    }else{
        int res = max(dfs(floot + 1, i), dfs(floot + 1, i + 1)) + g[floot][i];
        arr[floot][i] = res;
        return res;
    }
}

int main()
{
    cin >> n;
    g = vector< vector<int> >(n + 1, vector<int>());
    arr = vector< vector<int> >(n + 1, vector<int>());
    for (int i = 1; i <= n; ++i)
    {
        int x;
        for (int k = 0; k < i; ++k)
        {
            cin >> x;
            g[i].push_back(x);
        }
    }
    for (int i = 1; i <= n; ++i)
    {
        arr[i] = vector<int>(i, -1);
    }
    cout << dfs(1, 0);
    return 0;
}