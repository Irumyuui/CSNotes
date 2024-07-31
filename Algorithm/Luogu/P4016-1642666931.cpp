#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

const int LEN = 1e3 + 10;
LL cost[LEN];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    LL n, k, sum;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> cost[i];
        cost[i] += cost[i - 1];
    }
    k = cost[n] / n;
    for (int i = 1; i < n; ++ i)
    {
        cost[i] = i * k - cost[i];
    }
    sort(cost, cost + n);
    LL ans = 0, ave = cost[n / 2];
    for (int i = 0; i < n; ++ i)
    {
        ans += llabs(ave - cost[i]);
    }
    cout << ans;
    return 0;
}