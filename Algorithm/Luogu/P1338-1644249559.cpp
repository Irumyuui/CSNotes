#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

const int N = 5e4 + 10;
LL cnt[N];
bool vis[N];
int ans[N];

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    fill(all(vis), false);
    fill(all(ans), -1);
    int n, m;
    cin >> n >> m;
    cnt[0] = 0;
    for (int i = 1; i <= n; ++ i){
        cnt[i] = cnt[i - 1] + i;
    }
    int len = n, tot = n;
    while (m > 0){
        int numcnt = lower_bound(cnt, cnt + n, m) - cnt;
        ans[tot] = n - numcnt;
        vis[n - numcnt] = true;
        m = m - numcnt;
        tot --;
    }
    for (int i = 1, j = 1; i <= n; ++ i){
        if (ans[i] != -1)
            continue;
        while (vis[j])
            j ++;
        ans[i] = j ++;
    }
    for (int i = 1; i <= n; ++ i)
        cout << ans[i] << ' ';
    return 0;
}