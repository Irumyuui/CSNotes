#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 1e5 + 115;
priority_queue<LL, vector<LL>, less<LL>>lq;
priority_queue<LL, vector<LL>, greater<LL>>rq;
// LL arr[LEN] = {0, }, n;

void solve(){
    LL n, x;
    cin >> n >> x;
    rq.push(x);
    cout << x << endn;
    for (int i = 2; i <= n; ++ i){
        cin >> x;
        if (x > rq.top()){
            rq.push(x);
        }else{
            lq.push(x);
        }
        while (lq.size() > rq.size()){
            rq.push(lq.top());
            lq.pop();
        }
        while (rq.size() > lq.size()){
            lq.push(rq.top());
            rq.pop();
        }
        if (i & 1){
            if (lq.size() > rq.size()){
                cout << lq.top() << endn;
            }else{
                cout << rq.top() << endn;
            }
        }
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    solve();
    return 0;
}