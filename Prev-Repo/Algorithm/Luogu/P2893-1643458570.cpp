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
    vector<int>v(n);
    for (auto &it : v) cin >> it;
    LL ans1 = 0, ans2 = 0;
    priority_queue<int>q1;
    for (auto it : v){
        q1.push(it);
        if (it < q1.top()){
            ans1 += q1.top() - it;
            q1.pop();
            q1.push(it);
        }
    }
    priority_queue<int, vector<int>, greater<int>>q2;   
    for (auto it : v){
        q2.push(it);
        if (it > q2.top()){
            ans2 += it  - q2.top();
            q2.pop();
            q2.push(it);
        }
    }
    cout << min(ans1, ans2) << '\n';
    return 0;
}