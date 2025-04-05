#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
const int LEN = 102 << 1;
LL head[LEN], tail[LEN], f[LEN][LEN];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i){
        cin >> head[i];
        head[i + n] = head[i];
    }
    // tail[1] = tail[n];
    for (int i = 1; i <= n << 1; ++ i)
    {
        if (i == n << 1)
            tail[i] = head[1];
        else
            tail[i] = head[i + 1];
    }
    for (int c = 1; c <= n; ++ c)
    {
        for (int i = 1; i <= (n << 1) - c; ++ i)
        {
            int j = i + c;
            for (int k = i; k < j; ++ k)
            {
                f[i][j] = max(f[i][j], f[i][k] + f[k + 1][j] + head[i] * head[k + 1] * tail[j]);
            }
        }
    }
    LL ans = 0;
    for (int i = 1; i <= n; ++ i)
    {
        ans = max(ans, f[i][i + n - 1]);
    }
    cout << ans;
    return 0;
}