#include <bits/stdc++.h>

using namespace std;

int arr[114][114], sum[114][114];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= m; ++ j)
        {
            cin >> arr[i][j];
        }
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= m; ++ j)
        {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + arr[i][j];
        }
    }
    int ans = 0;
    for (int len = 1; len <= min(n, m); ++ len)
    {
        for (int i = len; i <= n; ++ i)
        {
            for (int j = len; j <= m; ++ j)
            {
                if (sum[i][j] - sum[i - len][j] - sum[i][j - len] + sum[i - len][j - len] == len * len){
                    ans = max(ans, len);
                }
            }
        }
    }
    cout << ans;
    return 0;
}