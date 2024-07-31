#include <bits/stdc++.h>

inline void FREIN(const char *text){freopen(text, "r", stdin);}
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

int n, k;
vector<int>ans;

bool dfs(int mult, int sum){
    if (mult == 1 && sum == 0){
        return true;
    }else if (sum == 0){
        return false;
    }
    for (int i = 1; i <= sum && i <= mult; ++ i){
        if (mult % i == 0){
            ans.push_back(i);
            if (dfs(mult / i, sum - i) == false){
                ans.pop_back();
            }else{
                return true;
            }
        }
    }
    return false;
}

void solve(){
    cin >> n >> k;
    dfs(n, k);
    if (ans.empty()){
        cout << -1 << endl;
    }else{
        cout << ans.size() << endl;
        for (auto it : ans)
            cout << it << ' ';
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}