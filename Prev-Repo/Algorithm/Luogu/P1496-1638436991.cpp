#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

class edge{
    public:
        LL l, r;
        edge(){this->l = this->r = 0;}
        edge(const LL l, const LL r){this->l = l; this->r = r;}
        bool operator<(const edge a) const{
            if (this->l == a.l){
                return this->r < a.r;
            }
            return this->l < a.l;
        } 
};

inline LL ABS(const edge &a){
    return llabs(a.l - a.r);
}

void solve(){
    LL n;
    cin >> n;
    if (n == 0){
        cout << 0 << endl;
        return;
    }
    vector<edge>v(n);
    for (auto &it : v) cin >> it.l >> it.r;
    sort(v.begin(), v.end(), less<edge>());
    edge t = v.front();
    LL ans = ABS(t);
    for (LL i = 1; i < n; ++ i){
        if (v[i].l < t.r && v[i].r < t.r){
            continue;
        }else if (v[i].l < t.r){
            ans += (ABS(v[i]) - (t.r - v[i].l));
            t.r = v[i].r;
        }else{
            ans += ABS(v[i]);
            t = v[i];
        }
    }
    cout << ans << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}