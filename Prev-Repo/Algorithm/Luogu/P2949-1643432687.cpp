#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<PLL>v(n);
    for (auto &it : v) cin >> it.first >> it.second;
    sort(all(v), [](const PLL &a, const PLL &b){
        return a.first == b.first ? a.second > b.second : a.first < b.first;
    });
    auto cmp = [](const PLL &a, const PLL &b){
        return a.second > b.second;
    };
    priority_queue<PLL, vector<PLL>, decltype(cmp)>q(cmp);
    LL ans = 0;
    for (auto it : v){
        if (it.first > q.size()){
            ans += it.second;
            q.push(it);
        }else if (it.second > q.top().second){
            ans -= q.top().second;
            q.pop();
            ans += it.second;
            q.push(it);
        }
    }
    cout << ans << '\n';
    return 0;
}