#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;

void solve(){
    LL ans = -0x7FFFFFFFFFFFFFFF, cnt, mini;
    cin >> cnt >> mini;
    while (-- cnt){
        LL x;
        cin >> x;
        ans = max(ans, x - mini);
        mini = min(x, mini);
    }
    cout << ans << endl;
}

int main(){
    FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}