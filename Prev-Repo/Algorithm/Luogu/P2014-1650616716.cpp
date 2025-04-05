#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e2 + 10;
vector<int> g[MAXN];
int w[MAXN];
int dp[MAXN][MAXN];
int n, m;

int dfs(int now) {
    int cnt = 1;
    for (auto nex : g[now]) {
        int ncnt = dfs(nex);

        for (int i = min(cnt, m); i >= 1; -- i) {
            for (int j = min(m, ncnt); j >= 1; -- j) {
                dp[now][i + j] = max(dp[now][i + j], dp[nex][j] + dp[now][i]);
            }
        }

        cnt += ncnt;
    }

    return cnt;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> n >> m;
    m += 1;
    for (int i = 1; i <= n; ++ i) {
        int x;
        cin >> x >> dp[i][1];
        g[x].push_back(i); 
    }

    dfs(0);
    
    cout << dp[0][m] << '\n';

    return 0;
}