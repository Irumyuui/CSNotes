#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

typedef long long LL;

LL ans = 0;
vector<int>sch, stu;

int bserch(int k){
    int ll = 0, rr = sch.size() - 1, mid;
    while (ll < rr){
        mid = ll + ((rr - ll) >> 1);
        if (k < sch[mid]){
            rr = mid;
        }else{
            ll = mid + 1;
        }
    }
    return ll;
}

void solve(){
    sort(sch.begin(), sch.end(), less<int>());
    for (auto its : stu){
        int it = bserch(its);
        if (it == sch.size()){
            ans += abs(its - sch[it]);
        }else if (it == 0){
            ans += abs(its - sch[0]);
        }else{
            ans += min(abs(its - sch[it]), abs(its - sch[it - 1]));
        }
    }
    cout << ans << endl;
}

int main(){
    FAST();
    //FREIN("in.in");
    int n, m;
    cin >> n >> m;
    sch = vector<int>(n);
    stu = vector<int>(m);
    for (auto &it : sch) cin >> it;
    for (auto &it : stu) cin >> it;
    solve();
    return 0;
}