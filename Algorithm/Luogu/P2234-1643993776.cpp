#include <bits/stdc++.h>
using namespace std;
using LL = long long;

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n;
    cin >> n;
    LL ans = 0;
    set<LL, less<LL>>s1;
    set<LL, greater<LL>>s2;
    cin >> ans;
    s1.insert(ans);
    s2.insert(ans);
    for (int i = 2; i <= n; ++ i){
        LL x;
        cin >> x;
        auto it1 = s1.lower_bound(x), it2 = s2.lower_bound(x);
        if (it1 == s1.end()){
            ans += llabs(*it2 - x);
        }else if (it2 == s2.end()){
            ans += llabs(*it1 - x);
        }else{
            ans += min(llabs(*it1 - x), llabs(*it2 - x));
        }
        s1.insert(x); s2.insert(x);
    }
    cout << ans;
    return 0;
}