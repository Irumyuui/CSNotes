#include <bits/stdc++.h>
using namespace std;
const int INFI = 0x7FFFFFFF;
const long long INFLL = 0x7FFFFFFFFFFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

LL n, p, s;
LL dp[1005];
PLL fil[1005];

void solve(){
    cin >> n >> p >> s;
    for (int i = 1; i <= n; ++ i){
        cin >> fil[i].first >> fil[i].second;
    }
    sort(fil + 1, fil + 1 + n);
    for (int i = 1; i <= n; ++ i){
        for (LL j = s; j >= 0; -- j){
            if (j >= fil[i].first){
                dp[j] = max(dp[j], dp[j - fil[i].first] + fil[i].second);
                if (dp[j] >= p){
                    cout << fil[i].first << endl;
                    return;
                }
            }
        }
    }
    cout << "No Solution!" << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}