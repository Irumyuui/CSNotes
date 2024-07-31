#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1e4;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> dp(n + 10, 0);
    dp[0] = dp[1] = 1;
    dp[2] = 2;
    int pre = 0;
    for (int i = 3; i <= n; ++ i){
        pre = (pre + dp[i - 3]) % MOD;
        dp[i] = (dp[i - 1] + dp[i - 2] + pre * 2) % MOD;
    }
    cout << dp[n] << '\n';

    return 0;
}