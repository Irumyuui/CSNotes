#include <bits/stdc++.h>

using namespace std;

const int INF = 1 << 30;

struct data
{
    int v, k;
    data(int v1, int k1) : v(v1), k(k1){};
    data() : v(INF){};
};

const int LEN = 3.2e4 + 10;
int f[LEN] = {0}, sumv, n;
data a[LEN][3];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> sumv >> n;
    int t = 0;
    for (int i = 1; i <= n; ++ i)
    {
        int v, k, p;
        cin >> v >> k >> p;
        if (p == 0){
            // ++ t;
            a[i][0].v = v;
            a[i][0].k = k;
        }else{
            if (a[p][1].v == INF){
                a[p][1].v = v;
                a[p][1].k = k;
            }else{
                a[p][2].v = v;
                a[p][2].k = k;
            }
        }
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = sumv; j >= a[i][0].v; -- j)
        {
            f[j] = max(f[j], f[j - a[i][0].v] + a[i][0]. v * a[i][0].k);
            if (a[i][1].v != INF){
                if (j >= a[i][0].v + a[i][1].v){
                    f[j] = max(f[j], f[j - (a[i][0].v + a[i][1].v)] + a[i][0].v * a[i][0].k + a[i][1].v * a[i][1].k);
                }
            }
            if (a[i][2].v != INF){
                if (j >= a[i][0].v + a[i][2].v){
                    f[j] = max(f[j], f[j - (a[i][0].v + a[i][2].v)] + a[i][0].v * a[i][0].k + a[i][2].v * a[i][2].k);
                }
                if (j >= a[i][0].v + a[i][1].v + a[i][2].v){
                    f[j] = max(f[j], f[j - (a[i][0].v + a[i][1].v + a[i][2].v)] + a[i][0].v * a[i][0].k + a[i][1].v * a[i][1].k + a[i][2].v * a[i][2].k);
                }
            }
        }
    }
    cout << f[sumv];
    return 0;
}