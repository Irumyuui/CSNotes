#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

void solve(){
    int n;
    cin >> n;
    stack<PII>s;
    vector<int>v(n + 1), ans(n + 1);    
    for (int i = 1; i <= n; ++ i)
        cin >> v[i];
    for (int i = n; i > 0; -- i){
        while (!s.empty() && s.top().first <= v[i]){
            s.pop();
        }
        if (s.empty()){
            ans[i] = 0;
        }else{
            ans[i] = s.top().second;
        }
        s.push({v[i], i});
    }
    for (int i = 1; i <= n; ++ i) cout << ans[i] << ' ';
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}