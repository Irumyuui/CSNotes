#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

const int N = 300;
int dp[N][N];

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> dp[i][i];
    int ans = 0;
    for (int k = 1; k < n; ++ k){
        for (int i = 1; i + k <= n; ++ i){
            int j = i + k;
            for (int c = i; c < j; ++ c){
                if (dp[i][c] == dp[c + 1][j]){
                    dp[i][j] = max(dp[i][j], dp[i][c] + 1);
                    ans = max(ans, dp[i][j]);
                }
            }
        }
    }
    cout << ans;
    return 0;
}