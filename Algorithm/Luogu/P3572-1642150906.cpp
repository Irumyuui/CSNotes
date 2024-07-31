#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int L = 1000010;
int n, arr[L], k, dp[L];

void solve()
{
    cin >> k;
    deque<int>deq;
    deq.push_back(1);
    for (int i = 2; i <= n; ++ i)
    {
        while (deq.front() + k < i)
        {
            deq.pop_front();
        }
        if (arr[i] >= arr[deq.front()]){
            dp[i] = dp[deq.front()] + 1;
        }else{
            dp[i] = dp[deq.front()];
        }
        while (!deq.empty() && (dp[deq.back()] > dp[i]) || (dp[deq.back()] == dp[i] && arr[deq.back()] < arr[i]))
        {
            deq.pop_back();
        }
        deq.push_back(i);
    }
    cout << dp[n] << '\n';
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> arr[i];
    int test;
    cin >> test;
    while (test --)
    {
        fill(dp, dp + L, 0);
        solve();
    }
    return 0;
}