#include <bits/stdc++.h>

using namespace std;

struct data
{
    int v, cnt;
    data() : v(0), cnt(0) {}
};

const int LEN = int(1e5 + 10) << 4;
int n, T, sumT, ret, alen = 0;

data arr[LEN], d[150];
int f1[LEN], f2[LEN]; 

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> T;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> d[i].v;
    }
    for (int i = 1; i <= n; ++ i)
    {
        cin >> d[i].cnt;
        sumT += d[i].v * d[i].cnt;
        ret = max(ret, T + d[i].v * d[i].cnt);
    }
    if (sumT < T){
        cout << -1;
        return 0;
    }
    fill(f1, f1 + LEN, 1 << 28);
    f1[0] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = d[i].v; j <= ret; ++ j)
        {
            f1[j] = min(f1[j], f1[j - d[i].v] + 1);
        }
    }
    for (int i = 1; i <= n; ++ i)
    {
        int _v = d[i].v, _cnt = d[i].cnt;
        int k = 1;
        while (_cnt >= k)
        {
            alen ++;
            arr[alen].v = k * _v;
            arr[alen].cnt = k;
            _cnt -= k;
            k <<= 1;
        }
        if (_cnt > 0){
            alen ++;
            arr[alen].cnt = _cnt;
            arr[alen].v = _cnt * _v;
        }
    }
    fill(f2, f2 + LEN, 1 << 28);
    f2[0] = 0;
    for (int i = 1; i <= alen; ++ i)
    {
        for (int j = ret; j >= arr[i].v; -- j)
        {
            f2[j] = min(f2[j], f2[j - arr[i].v] + arr[i].cnt);
        }
    }
    int ans = 1 << 28;
    for (int i = T; i <= ret; ++ i)
    {
        ans = min(ans, f2[i] + f1[i - T]);
    }
    if (ans == (1 << 28)){
        cout << -1;
    }else{
        cout << ans;
    }
    return 0;
}