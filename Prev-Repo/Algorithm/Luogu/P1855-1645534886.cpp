#include <bits/stdc++.h>

#define all(container) std::begin(container), std::end(container)
#define range(iterator, container) for (auto &iterator : container)
#define crange(iterator, container) for (const auto &iterator : container)
#define cauto const auto
#define clear(array) std::memset(array, 0, sizeof(array))

using ll = long long;
using LL = __int128_t;

struct date {
    int m, t;
}arr[110];

int dp[110][210][210];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);

    int n, M, T;
    std::cin >> n >> M >> T;

    for (int i = 1; i <= n; ++ i) {
        std::cin >> arr[i].m >> arr[i].t;
    }

    for (int i = 1; i <= n; ++ i) {
        const int &m = arr[i].m, &t = arr[i].t;
        for (int j = M; j >= 0; -- j) {
            for (int k = T; k >= 0; -- k) {
                if (j >= m) {
                    if (k >= t) {
                        dp[i][j][k] = std::max({dp[i - 1][j][k], dp[i - 1][j - m][k], dp[i - 1][j][k - t], dp[i - 1][j - m][k - t] + 1});
                    } else {
                        dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i - 1][j - m][k]);
                    }
                } else {
                    if (k >= t) {
                        dp[i][j][k] = std::max(dp[i - 1][j][k], dp[i - 1][j][k - t]);
                    } else {
                        dp[i][j][k] = dp[i - 1][j][k];
                    }
                }
            }
        }
    }

    std::cout << dp[n][M][T] << '\n';

    return 0;
}