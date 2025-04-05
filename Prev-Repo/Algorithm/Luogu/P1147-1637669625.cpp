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
    int n, sum = 0;
    cin >> n;
    deque<int>ans;
    for (int i = 1; i < n; ++ i){
        sum += i;
        ans.push_back(i);
        while (sum > n){
            sum -= ans.front();
            ans.pop_front();
        }
        if (sum == n){
            cout << ans.front() << ' ' << ans.back() << endl;
        }
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}