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
    vector<PII>v(n);
    for (auto &it : v) cin >> it.first >> it.second;
    sort(all(v), [](const PII &a, const PII &b){
        return a.second < b.second;
    });
    auto cmp = [](const PII &a, const PII &b){
        return a.first < b.first;
    };
    priority_queue<PII, vector<PII>, decltype(cmp)>q(cmp);
    int t = 0;
    for (auto it : v){
        if (it.first + t <= it.second){
            q.push(it);
            t += it.first;
        }else if (it.first < q.top().first){
            t -= q.top().first;
            t += it.first;
            q.pop();
            q.push(it);
        }
        // cout << q.top().first << ' ' << q.top().second << '\n';
        // cout << t << '\n';
    }
    cout << q.size();
    return 0;
}