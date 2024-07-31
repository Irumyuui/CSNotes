#include <iostream>
#include <vector>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;

vector<PII>heal;
int dp[101][1001];

int main()
{
    int time, n;
    cin >> time >> n;
    heal = vector<PII>(n + 1);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> heal[i].first >> heal[i].second;
    }
    int res = -1;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = time; j >= 0; -- j)
        {
            if (j >= heal[i].first){
                dp[i][j] = max(dp[i - 1][j - heal[i].first] + heal[i].second, dp[i - 1][j]);
            }else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << dp[n][time] << endl;
    return 0;
}