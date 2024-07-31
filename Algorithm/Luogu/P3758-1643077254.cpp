#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)

typedef long long LL;

const LL MOD = 2017;
int n, m, t;

struct Matrix
{
    LL arr[31][31];
    Matrix()
    {
        fill(arr[0], arr[0] + 961, 0);
    }
    Matrix basic()
    {
        *this = Matrix();
        for (int i = 0; i < 31; ++ i)
        {
            this->arr[i][i] = 1;
        }
        return *this;
    }
    Matrix clear()
    {
        fill(arr[0], arr[0] + 961, 0);
        return *this;
    }
};

Matrix operator * (const Matrix &le, const Matrix &ri)
{
    Matrix res = Matrix().clear();
    for (int i = 0; i <= n; ++ i)
    {
        for (int j = 0; j <= n; ++ j)
        {
            for (int k = 0; k <= n; ++ k)
            {
                res.arr[i][j] += le.arr[i][k] * ri.arr[k][j];
                res.arr[i][j] %= MOD;
            }
        }
    }
    return res;
}

Matrix MQPow(Matrix a, LL i)
{
    Matrix res = Matrix().basic();
    while (i)
    {
        if (i & 1)
            res = res * a;
        a = a * a;
        i >>= 1;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    Matrix x;
    cin >> n >> m;
    for (int i = 0; i <= n; ++ i)
    {
        x.arr[i][0] = 1;
        x.arr[i][i] = 1;
    }
    for (int i = 1; i <= m; ++ i)
    {
        int a, b;
        cin >> a >> b;
        x.arr[a][b] = 1;
        x.arr[b][a] = 1;
    }
    cin >> t;
    Matrix res = MQPow(x, t);
    int ans = 0;
    for (int i = 0; i <= n; ++ i)
    {
        ans = (ans + res.arr[1][i]) % MOD;
    }
    cout << ans;
    return 0;
}