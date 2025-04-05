#include <bits/stdc++.h>
using namespace std;

const int LEN = 5e5 + 10;
// array<int, LEN>arr;
int arr[LEN];
int n, ques;

inline int lowbit(int x)
{
    return x & (-x);
}

int query(int k)
{
    int res = 0;
    while (k)
    {
        res += arr[k];
        k -= lowbit(k);
    }
    return res;
}

void add(int k, int ad)
{
    while (k <= n)
    {
        arr[k] += ad;
        k += lowbit(k);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> ques;
    for (int i = 1; i <= n; ++ i)
    {
        int x;
        cin >> x;
        add(i, x);
    }
    while (ques --)
    {
        int mp, x, y;
        cin >> mp >> x >> y;
        if (mp == 1){
            add(x, y);
        }else{
            cout << query(y) - query(x - 1) << '\n';
        }
    }
    return 0;
}