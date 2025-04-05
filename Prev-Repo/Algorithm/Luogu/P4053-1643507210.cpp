#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
using PII = pair<int, int>;
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<PII>v(n);
    for (auto &it : v) cin >> it.first >> it.second;
    sort(all(v), [](const PII &a, const PII &b){
        return a.second < b.second;
    });
    priority_queue<int>q;
    int t = 0;
    for (auto it : v){
        if (t + it.first <= it.second){
            q.push(it.first);
            t += it.first;
        }else if (!q.empty() && it.first < q.top()){
            t -= q.top(); q.pop();
            t += it.first; q.push(it.first);
        }
    }
    cout << q.size();
    return 0;
}