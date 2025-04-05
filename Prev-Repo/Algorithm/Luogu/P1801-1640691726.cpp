#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

int k, size, n, m, x;
priority_queue<int, vector<int>, less<int>>lq;
priority_queue<int, vector<int>, greater<int>>rq;
const int LEN = 2e5 + 115;
int arr[LEN];

void solve(){
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
    }
    rq.push(arr[++ size]);
    for (int i = 1; i <= m; ++ i){
        cin >> x;
        for (; size < x;){
            size ++;
            if (arr[size] > rq.top()){
                rq.push(arr[size]);
            }else{
                lq.push(arr[size]);
            }
        }
        while (lq.size() > i){
            rq.push(lq.top());
            lq.pop();
        }
        while (lq.size() < i){
            lq.push(rq.top());
            rq.pop();
        }
        cout << lq.top() << endn;
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