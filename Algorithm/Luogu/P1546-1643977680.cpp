#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

int n;
vector<int>dad;

int Find(int v){
    if (dad[v] != -1)
        return dad[v] = Find(dad[v]);
    return v;
}

bool Union(int a, int b){
    a = Find(a); b = Find(b);
    if (a != b){
        dad[a] = b;
        return true;
    }
    return false;
}

struct edge{
    int u, v, l;
    bool operator < (const edge &a) const{
        return l < a.l;
    }  
    edge(int u_, int v_, int l_) : u(u_), v(v_), l(l_){};
};

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;    
    dad.resize(n + 1, -1);
    vector<edge>v;
    for (int i = 1; i <= n; ++ i){
        for (int j = 1; j <= n; ++ j){
            int l;
            cin >> l;
            v.push_back(edge(i, j, l));
        }
    }
    sort(all(v));
    int ans = 0, cnt = 0;
    for (cauto &it : v){
        if (Union(it.u, it.v)){
            ans += it.l;
            cnt ++;
            if (cnt >= n - 1)
                break;
        }
    }
    cout << ans;
    return 0;
}