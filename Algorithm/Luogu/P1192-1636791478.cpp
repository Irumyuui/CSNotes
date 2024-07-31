#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
const int modp = 100003;

int main()
{
    cin.tie(0);
    int floor, k;
    cin >> floor >> k;
    vector<LL>dp(floor + 1, 0);
    dp[0] = dp[1] = 1;
    for (int i = 2; i <= floor; ++ i)
    {
        for (int j = i; j >= 0 && j >= i - k; -- j)
        {
            dp[i] += dp[j];
            dp[i] %= modp;
        }
    }
    cout << dp[floor];
    return 0;
}