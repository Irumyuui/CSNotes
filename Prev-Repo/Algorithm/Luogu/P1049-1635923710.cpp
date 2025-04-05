#include <iostream>
#include <vector>
using namespace std;

int dp[31][20001];
vector<int>w;

int main()
{
    int size, n;
    cin >> size >> n;
    w = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> w[i];
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = size; j >= 0; -- j)
        {
            if (j >= w[i]){
                dp[i][j] = max(dp[i - 1][j - w[i]] + w[i], dp[i - 1][j]);
            }else{
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << size - dp[n][size] << endl;
    return 0;
}