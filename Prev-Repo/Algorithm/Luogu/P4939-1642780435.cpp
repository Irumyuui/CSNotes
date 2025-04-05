#include <bits/stdc++.h>

using namespace std;

const int LEN = 1e7 + 10;
long long d[LEN], n;

inline int lowbit(int x)
{
    return x & -x;
}

void add(int x, int k)
{
    while (x <= n)
    {
        d[x] += k;
        x += lowbit(x);
    }
}

long long query(int x)
{
    long long res = 0;
    while (x)
    {
        res += d[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> n >> t;
    while (t --)
    {
        int c;
        cin >> c;
        if (c == 0){
            int l, r;
            cin >> l >> r;
            add(l, 1);
            add(r + 1, -1);
        }else{
            int x;
            cin >> x;
            cout << query(x) << '\n';
        }
    }
    return 0;
}