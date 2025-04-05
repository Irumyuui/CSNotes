#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e5 + 10;
LL arr[LEN], dp[LEN] = {0, }, n, k, res = 0, ans = 0;
deque<LL>deq;

void solve(){
    cin >> n >> k;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
        res += arr[i];
        // cout << arr[i] << ' ';
    }
    // cout << ans << endn;
    deq.push_front(0);
    for (int i = 1; i <= n; ++ i){
        while (!deq.empty() && deq.front() + k + 1 < i){
            deq.pop_front();
        }
        dp[i] = dp[deq.front()] + arr[i];
        while (!deq.empty() && dp[deq.back()] >= dp[i]){
            deq.pop_back();
        }
        deq.push_back(i);
        // cout << dp[deq.front()] << ' ';
        // cout << dp[i] << ' ';
    }
    for (int i = n; i >= n - k; -- i){
        ans = max(ans, res - dp[i]);
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