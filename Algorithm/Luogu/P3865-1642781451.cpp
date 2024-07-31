#include <bits/stdc++.h>

using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

const int LEN = 1e5 + 10;
int f[LEN][22];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, q;
    // cin >> n >> q;
    n = read(), q = read();
    for (int i = 1; i <= n; ++ i)
    {
        f[i][0] = read();
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
        // cin >> l >> r;
        l = read(), r = read();
        int j = log2(r - l + 1);
        cout << max(f[l][j], f[r - (1 << j) + 1][j]) << '\n';
    }
    return 0;
}