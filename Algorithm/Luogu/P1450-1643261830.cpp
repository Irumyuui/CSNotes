#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

const int N = 1e5 + 10;
LL c[5], d[5], dp[N];

void solve()
{
    LL s;
    cin >> d[1] >> d[2] >> d[3] >> d[4] >> s;
    LL ans = dp[s];
    for (int k = 1; k < (1 << 4); ++ k)
    {
        LL now = s, isd = 0;
        for (int i = k, j = 1; i; i >>= 1, j ++)
        {
            if (i & 1){
                isd ^= 1;
                now -= (d[j] + 1) * c[j];
            }
        }
        if (now >= 0){
            if (isd){
                ans -= dp[now];
            }else{
                ans += dp[now];
            }
        }
    }
    cout << ans << '\n';
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> c[1] >> c[2] >> c[3] >> c[4];
    dp[0] = 1;
    for (int i = 1; i <= 4; ++ i)
        for (int j = c[i]; j < N; ++ j)
            dp[j] += dp[j - c[i]];
    int t;
    cin >> t;
    while (t --)
    {
        solve();
    }
    return 0;
}