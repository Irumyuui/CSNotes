#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    list<int>l;
    int n;
    cin >> n;
    vector<bool>v(n + 1, false);
    vector<list<int>::iterator>pos(n + 1);
    l.push_back(1);
    pos[1] = l.begin();
    for (int i = 2; i <= n; ++ i){
        int p, k;
        cin >> p >> k;
        auto it = pos[p];
        if (k == 0){
            pos[i] = l.insert(it, i);
        }else{
            it ++;
            pos[i] = l.insert(it, i);
        }
    }   
    int m;
    cin >> m;
    for (int i = 1; i <= m; ++ i){
        int k;
        cin >> k;
        v[k] = true;
    }
    for (auto it : l){
        if (!v[it]) cout << it << ' ';
    }
    return 0;
}