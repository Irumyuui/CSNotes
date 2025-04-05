/**
 * @file P2014 [CTSC1997] 选课.cpp
 * @author Cieru
 * @brief 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e2 + 70;
int n, m;
vector<int> g[MAXN];
int w[MAXN];
int dp[MAXN][MAXN];

int dfs(int now) {
    int cnt = 1;
    dp[now][1] = w[now];
    for (auto nex : g[now]) {
        int tmp = dfs(nex);
        for (int i = min(cnt, m); i > 0; -- i) {
            for (int j = 1; j <= tmp && i + j <= m; ++ j) {
                dp[now][i + j] = max(dp[now][i + j], dp[now][i] + dp[nex][j]);
            }
        }
        cnt += tmp;
    }
    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        int d;
        cin >> d >> w[i];
        g[d].push_back(i);
    }

    m ++;
    dfs(0);
    cout << dp[0][m];

    return 0;
}