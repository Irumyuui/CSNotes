#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

int n;
priority_queue<string, vector<string>, greater<string>>q;
string str;

void solve(){
    while (!q.empty()){
        string st = q.top();
        q.pop();
        if (st.size() < str.size()){
            continue;
        }
        bool no = false;
        for (int i = 0; i < str.size(); ++ i){
            if (st[i] != str[i]){
                no = true;
                break;
            }
        }
        if (no){
            continue;
        }
        cout << st << endn;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++ i){
        cin >> str;
        q.push(str);
    }
    cin >> str;
    solve();
    return 0;
}