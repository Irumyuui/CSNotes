#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

LL n, m, x;
string str;
priority_queue<LL, vector<LL>, less<LL>>lq;
priority_queue<LL, vector<LL>, greater<LL>>rq;

void add(LL x){
    if (x > rq.top()) rq.push(x);
    else lq.push(x);
    while (rq.size() > lq.size()){
        lq.push(rq.top());
        rq.pop();
    }
    while (lq.size() > rq.size()){
        rq.push(lq.top());
        lq.pop();
    }
}

void solve(){
    cin >> n >> x;
    rq.push(x);
    for (int i = 1; i < n; ++ i){
        cin >> x;
        add(x);
    }
    cin >> m;
    while (m --){
        cin >> str;
        if (str == "add"){
            cin >> x;
            add(x);
        }else{
            cout << (rq.size() > lq.size() ? rq.top() : lq.top()) << endn;
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