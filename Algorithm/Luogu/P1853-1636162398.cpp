#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;

const int N = 1e7 + 5;
const int N_ = 100;

// vector<LL>dp(N, 0);
LL dp[N];
// vector<PII>w(N_);
PII w[N_];

inline LL f(const LL &a, const LL &b)
{
    return a > b ? a : b;
}

int main()
{
    cin.tie(0);
    int sm, years, n;
    cin >> sm >> years >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> w[i].first >> w[i].second;
    }
    for (int i = 0; i < years; ++ i)
    {
        for (int j = 1; j <= n; ++ j)
        {
            for (int k = w[j].first; k <= sm; ++ k)
            {
                dp[k] = f(dp[k - w[j].first] + w[j].second, dp[k]);
            }
        }
        sm += dp[sm];
    }
    cout << sm;
    return 0;
}