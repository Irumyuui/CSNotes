#include <bits/stdc++.h>

using namespace std;

const long long INF = 1 << 30;
const int LEN = 55;
long long len[LEN], w[LEN], f[LEN][LEN][2];
int x, n, sta;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> sta;
    fill(f[0][0], f[0][0] + LEN * LEN * 2, INF);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> len[i] >> w[i];
        w[i] += w[i - 1];
    }
    f[sta][sta][1] = f[sta][sta][0] = 0;
    for (int c = 1; c <= n; ++ c)
    {
        for (int i = 1; i + c <= n; ++ i)
        {
            int j = i + c;
            f[i][j][0] = min(f[i][j][0], min(f[i + 1][j][0] + abs(len[i] - len[i + 1]) * (w[n] - w[j] + w[i]), f[i + 1][j][1] + abs(len[i] - len[j]) * (w[n] - w[j] + w[i])));

            f[i][j][1] = min(f[i][j][1], min(f[i][j - 1][0] + abs(len[j] - len[i]) * (w[n] - w[j - 1] + w[i - 1]), f[i][j - 1][1] + abs(len[j] - len[j - 1]) * (w[n] - w[j - 1] + w[i - 1])));
        }
    }
    cout << min(f[1][n][0], f[1][n][1]);
    return 0;
}