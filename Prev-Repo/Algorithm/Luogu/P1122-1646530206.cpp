#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;

vector<int>g[MAXN];
int w[MAXN], dp[MAXN];

void dfs(int now, int fa) {
    // dp[now] = max(w[now], 0);
    dp[now] = w[now];
    for (auto nex : g[now]) {
        if (nex == fa) continue;
        dfs(nex, now);
        dp[now] = max(dp[now], dp[now] + dp[nex]);
        // dp[now] += dp[nex];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> w[i];
    for (int i = 1; i < n; ++ i) {
        int a, b; cin >> a >> b;
        g[a].push_back(b); g[b].push_back(a);
    }
    dfs(1, 0);
    // cout << dp[1] << '\n';
    int ans = -(1 << 30);
    for (int i = 1; i <= n; ++ i) 
        ans = max(ans, dp[i]);
    cout << ans;

    return 0;
}