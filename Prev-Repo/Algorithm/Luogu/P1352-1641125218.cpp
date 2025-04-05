#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

vector<vector<int>>g, dp;
vector<int>h;
vector<bool>vis;
int n, a, b;

void dfs(int v){
    dp[v][0] = 0;
    dp[v][1] = h[v];
    for (auto it : g[v]){
        dfs(it);
        dp[v][0] += max(dp[it][0], dp[it][1]);
        dp[v][1] += dp[it][0];
    }
}

void solve(){
    cin >> n;
    g = vector<vector<int>>(n + 1, vector<int>());
    dp = vector<vector<int>>(n + 1, vector<int>(2, 0));
    h = vector<int>(n + 1);
    vis = vector<bool>(n + 1, false);
    for (int i = 1; i <= n; ++ i){
        cin >> h[i];
    }
    for (int i = 1; i < n; ++ i){
        cin >> a >> b;
        g[b].push_back(a);
        vis[a] = true;
    }
    int boss;
    for (int i = 1; i <= n; ++ i){
        if(!vis[i]){
            boss = i;
            break;
        } 
    }
    dfs(boss);
    cout << max(dp[boss][0], dp[boss][1]) << endn;
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}