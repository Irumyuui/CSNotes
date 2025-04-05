#include <iostream>
#include <vector>

using namespace std;

int dp[10005];
int arr[102];

int main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> arr[i];
    }
    dp[0] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = m; j >= arr[i]; -- j)
        {
            dp[j] += dp[j - arr[i]];
        }
    }
    cout << dp[m];
    return 0;
}