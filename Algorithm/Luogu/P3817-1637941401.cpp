#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

void solve(){
    LL n, x, sum = 0;
    cin >> n >> x;
    vector<LL>candy(n);
    for (auto &it : candy) cin >> it;
    if (candy[0] > x){
        sum += candy[0] - x;
        candy[0] = x;
    }
    for (int i = 1; i < n; ++ i){
        if (candy[i - 1] + candy[i] > x){
            sum += (candy[i - 1] + candy[i] - x);
            candy[i] -= (candy[i - 1] + candy[i] - x);
        }
    }
    cout << sum;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}