#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INFI = 0x7fffffff;
const LL INFL = 0x7fffffffffffffff;

const int LEN = 2e5 + 115;
int n, l, r;
LL ans = -INFL;
LL dp[LEN] = {0};
LL arr[LEN];
deque<LL>dq;

void solve(){
    for (int i = 0; i <= n; ++ i){
        dp[i] = -INFL;
    }
    dp[0] = 0;
    for (int i = l; i <= n; ++ i){
        while (!dq.empty() && dp[dq.back()] < dp[i - l]){
            dq.pop_back();
        }
        dq.push_back(i - l);
        while (dq.front() < i - r){
            dq.pop_front();
        }
        dp[i] = dp[dq.front()] + arr[i];
        if (i + r > n){
            ans = max(ans, dp[i]);
        }
    }
    cout << ans << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n >> l >> r;
    for (int i = 0; i <= n; ++ i){
        cin >> arr[i];
    }
    solve();
    return 0;
}