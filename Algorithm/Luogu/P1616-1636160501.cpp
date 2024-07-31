#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;

const int N = 1e7 + 5;
const int N_ = 1e4 + 5;
vector<LL>dp(N, 0);
vector<PLL>w(N_);

int main()
{
    cin.tie(0);
    int st, n;
    cin >> st >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> w[i].first >> w[i].second;
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = w[i].first; j <= st; ++ j)
        {
            dp[j] = max(dp[j - w[i].first] + w[i].second, dp[j]);
        }
    }
    cout << dp[st];
    return 0;
}