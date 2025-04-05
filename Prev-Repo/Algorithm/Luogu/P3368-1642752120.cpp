#include <bits/stdc++.h>

using namespace std;

const int LEN = 1e6 + 10;

int arr[LEN], mk[LEN];
int n, m;

inline int lowbit(int x)
{
    return x & (-x);
}

int query(int x)
{
    int res = 0;
    while (x)
    {
        res += mk[x];
        x -= lowbit(x);
    }
    return res;
}

void change(int x, int v)
{
    while (x <= n)
    {
        mk[x] += v;
        x += lowbit(x);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> arr[i];
    }
    int c, x, y, k;
    while (m --)
    {
        cin >> c;
        if (c == 1){
            cin >> x >> y >> k;
            change(x, k);
            change(y + 1, -k);
        }else{
            cin >> x;
            cout << arr[x] + query(x) << '\n';
        }
    }
    return 0;
}