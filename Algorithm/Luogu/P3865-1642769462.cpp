#include <bits/stdc++.h>

using namespace std;

const int LEN = 1e5 + 10;
int f[LEN][22];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> f[i][0];
    }
    for (int j = 1; j <= 21; ++ j)
    {
        for (int i = 1; i + (1 << j) - 1 <= n; ++ i)
        {
            f[i][j] = max(f[i][j - 1], f[i + (1 << j - 1)][j - 1]);
        }
    }
    while (q --)
    {
        int l, r;
        cin >> l >> r;
        int j = log2(r - l + 1);
        cout << max(f[l][j], f[r - (1 << j) + 1][j]) << '\n';
    }
    return 0;
}