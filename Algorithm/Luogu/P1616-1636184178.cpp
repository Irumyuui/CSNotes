#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;

const int N = 1e7 + 5;
const int N_ = 1e4 + 5;
LL dp[N];
PLL weight[N_];

int main()
{
    // cin.tie(0);
    int time, m;
    cin >> time >> m;
    for (int i = 1; i <= m; ++ i)
    {
        cin >> weight[i].first >> weight[i].second;
    }
    for (int i = 0; i <= m; ++ i)
    {
        for (int j = weight[i].first; j <= time; ++ j)
        {
            dp[j] = max(dp[j - weight[i].first] + weight[i].second, dp[j]);
        }
    }
    cout << dp[time];
    return 0;
}