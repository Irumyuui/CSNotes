#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;

class cloudy
{
    public:
        int d;
        LL monney, val;
};

vector<cloudy>dad;
vector<LL>dp;

LL FIND(LL a)
{
    if (dad[a].d != a){
        dad[a].d = FIND(dad[a].d);
    }
    return dad[a].d;
}

void Union(LL a, LL b)
{
    a = FIND(a);
    b = FIND(b);
    if (a != b){
        dad[b].d = a;
        dad[a].monney += dad[b].monney;
        dad[a].val += dad[b].val;
    }
}

int main()
{
    int n, m, w;
    cin >> n >> m >> w;
    dad = vector<cloudy>(n + 1);
    dp = vector<LL>(w + 1, 0);
    for (int i = 1; i <= n; ++ i)
    {
        dad[i].d = i;
        cin >> dad[i].monney >> dad[i].val;
    }
    while (m --)
    {
        int a, b;
        cin >> a >> b;
        Union(a, b);
    }
    for (int i = 1; i <= n; ++ i)
    {
        if (dad[i].d == i){
            for (int j = w; j >= dad[i].monney; -- j)
            {
                dp[j] = max(dp[j], dp[j - dad[i].monney] + dad[i].val);
            }
        }
    }
    cout << dp[w];
    return 0;
}