#include <bits/stdc++.h>

#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

inline void FREIN(const char *text){
    freopen(text, "r", stdin);
}

template<class Type> inline void ddebug(const Type X){
    std::cerr << "debug : " << X << std::endl;
}

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

void solve(){
    int n;
    cin >> n;
    int res = 0, x;
    while (n --){
        cin >> x;
        res ^= x;
    }
    cout << res << endl;
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}