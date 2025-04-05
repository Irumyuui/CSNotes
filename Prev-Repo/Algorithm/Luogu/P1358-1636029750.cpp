#include <iostream>
#include <vector>

using namespace std;

const long long mod = 10007;
vector<vector<long long>>v;

int main()
{
    long long n, m;
    cin >> n >> m;
    v = vector<vector<long long>>(n + 1, vector<long long>());
    for (long long i = 0; i <= n; ++ i)
    {
        v[i] = vector<long long>(101);
        if (i < 101)
            v[i][0] = v[i][i] = 1;
        else
            v[i][0] = 1;
        for (long long j = 1; j < i && j < 101; ++ j)
        {
            v[i][j] = (v[i - 1][j - 1] + v[i - 1][j]) % mod;
        }
    }
    long long res = 1;
    for (long long i = 0; i < m; ++ i)
    {
        long long x;
        cin >> x;
        res = (res * v[n][x]) % mod;
        n -= x;
    }
    cout << res;
    return 0;
}