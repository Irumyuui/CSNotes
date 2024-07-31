#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int INFI = 0x7fffffff;
const LL INFL = 0x7fffffffffffffff;

const int LEN = 300;
int n;
int arr[LEN], dpa[LEN][LEN] = {0, }, dpi[LEN][LEN] = {0, };

void solve(){
    for (int len = 1; len < n << 1; ++ len){
        for (int i = 1; i <= (n << 1) - len; ++ i){
            int j = i + len;
            dpi[i][j] = INFI;
            for (int k = i; k < j; ++ k){
                dpa[i][j] = max(dpa[i][j], dpa[i][k] + dpa[k + 1][j] + arr[j] - arr[i - 1]);
                dpi[i][j] = min(dpi[i][j], dpi[i][k] + dpi[k + 1][j] + arr[j] - arr[i - 1]);
            }
        }
    }
    int ansa = 0, ansi = INFI;
    for (int i = 1; i < n; ++ i){
        ansa = max(ansa, dpa[i][n + i - 1]);
        ansi = min(ansi, dpi[i][n + i - 1]);
    }
    cout << ansi << endl << ansa << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    cin >> n;
    vector<int>v((n << 1) + 1);
    for (int i = 1; i <= n; ++ i){
        cin >> v[i];
        v[n + i] = v[i];
    }
    for (int i = 1; i <= n << 1; ++ i){
        arr[i] = arr[i - 1] + v[i];
    }
    solve();
    return 0;
}