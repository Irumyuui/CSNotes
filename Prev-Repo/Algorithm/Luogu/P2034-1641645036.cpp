#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e5 + 10;
LL arr[LEN], dp[LEN] = {0, }, n, k, res = 0, ans = 0;

void solve(){
    cin >> n >> k;
    deque<LL>q;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
        res += arr[i];
    }
    q.push_back(0);
    for (int i = 1; i <= n; ++ i){
        while (!q.empty() && q.front() + k + 1 < i){
            q.pop_front();
        }
        dp[i] = dp[q.front()] + arr[i];
        while (!q.empty() && dp[q.back()] >= dp[i]){
            q.pop_back();
        }
        q.push_back(i);
        if (i + k >= n){
            ans = max(ans, res - dp[i]);
        }
    }
    cout << ans << endn;
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