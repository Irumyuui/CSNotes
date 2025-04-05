#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INFI = 0x7fffffff;
const LL INFL = 0x7fffffffffffffff;

const int LEN = 2e6 + 115;
LL arr[LEN], sum[LEN] = {0, }, ans = 0, n;

void solve(){
    deque<LL>q;
    for (int i =  1; i < (n << 1); ++ i){
        while (!q.empty() && sum[q.front()] > sum[i]){
            q.pop_front();
        }
        q.push_front(i);
        if (i < n){
            continue;
        }
        while (q.back() <= i - n){
            q.pop_back();
        }
        if (sum[q.back()] - sum[i - n] >= 0){
            ans ++;
        }
    }
    cout << ans << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
        arr[i + n] = arr[i];
    }
    for (int i = 1; i <= (n << 1); ++ i){
        sum[i] = sum[i - 1] + arr[i];
    }
    solve();
    return 0;
}