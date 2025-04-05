#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    LL n, m;
    cin >> n >> m;
    vector<PLL>v(n + 1);
    v[0].first = v[0].second = 0;
    for (int i = 1; i <= n; ++ i) cin >> v[i].first >> v[i].second;
    sort(v.begin() + 1, v.end());
    LL ans = 0, ans_ = 0, t = 0;
    priority_queue<LL>q;
    for (int i = 1; i <= n; ++ i){
        LL at = v[i].first - v[i - 1].first;
        while (!q.empty() && t + at + v[i].second > m){
            t -= q.top();
            ans_ --;
            q.pop();            
        }
        if (t + at + v[i].second <= m){
            t += at + v[i].second;
            ans_ ++;
        }
        q.push(v[i].second);
        ans = max(ans, ans_);        
    }
    cout << ans;
    return 0;
}