#include <iostream>
#include <vector>

using namespace std;

long long dp[26][30001];
vector< pair<long, long> >v;

int main()
{
    int money, n;
    cin >> money >> n;
    v = vector< pair<long, long> >(n + 1);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> v[i].first >> v[i].second;
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = money; j >= 0; -- j)
        {
            if (j >= v[i].first){
                dp[i][j] = max(dp[i - 1][j - v[i].first] + v[i].first * v[i].second, dp[i - 1][j]);
            }else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][money] << endl;
    return 0;
}