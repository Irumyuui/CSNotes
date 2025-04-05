#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INFI = 0x7fffffff;
const LL INFL = 0x7fffffffffffffff;

const int LEN = 5e5 + 115;
LL sum[LEN] = {0, }, n, m, ans = -INFL;

void solve(){
    deque<LL>q;
    q.push_back(0);
    for (int i = 1; i <= n; ++ i){
        while (q.front() + m < i){
            q.pop_front();
        }
        ans = max(ans, sum[i] - sum[q.front()]);
        while (!q.empty() && sum[q.back()] >= sum[i]){
            q.pop_back();
        }
        q.push_back(i);
    }
    cout << ans << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i){
        LL x;
        cin >> x;
        sum[i] = sum[i - 1] + x;
    }
    solve();
    return 0;
}