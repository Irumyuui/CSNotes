#include <bits/stdc++.h>
using namespace std;

#define ALL(x) std::begin(x), std::end(x)
using ll = long long;

const int N = 32768;
ll dp[N + 1][5] = {1};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    for (int i = 1; i <= N; ++ i) {
        for (int j = i * i; j <= N; ++ j) {
            for (int k = 1; k <= 4; ++ k) {
                dp[j][k] += dp[j - i * i][k - 1];
            }
        }
    }

    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        int x;
        cin >> x;

        ll ans = 0;
        for (int j = 0; j < 5; ++ j) {
            ans += dp[x][j];
        }
        cout << ans << '\n';
    }
    
    return 0;
}