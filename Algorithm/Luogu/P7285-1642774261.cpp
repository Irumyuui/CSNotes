#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    long long cnt[2];
    int test;
    cin >> test;
    while (test --)
    {
        int n;
        cin >> n;
        cnt[0] = cnt[1] = 0;
        for (int i = 1; i <= n; ++ i)
        {
            int x;
            cin >> x;
            cnt[x] ++;
        }
        cout << n - cnt[0] << '\n';
        for (int i = 1; i <= n; ++ i)
            cout << 1 << ' ';
        cout << '\n';
    }
    return 0;
}