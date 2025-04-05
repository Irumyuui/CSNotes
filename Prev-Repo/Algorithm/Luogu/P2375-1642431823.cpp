#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const LL MOD = 1000000007LL;
const LL LEN = 1e6 + 115;
char str[LEN];
LL nex[LEN], num[LEN], len, ans, cnt;

void solve(){
    ans = 1;
    num[1] = 1;
    nex[0] = nex[1] = 0;
    cin >> str + 1;
    len = strlen(str + 1);
    int k = 0;
    for (int i = 2; i <= len; ++ i)
    {
        while (k && str[k + 1] != str[i]){
            k = nex[k];
        }
        if (str[i] == str[k + 1]){
            k ++;
        }
        nex[i] = k;
        num[i] = num[k] + 1;
    }
    k = 0;
    for (int i = 1; i <= len; ++ i)
    {
        while (k && str[k + 1] != str[i]){
            k = nex[k];
        }
        if (str[k + 1] == str[i]){
            k ++;
        }
        while (k > i >> 1){
            k = nex[k];
        }
        ans = ans * (num[k] + 1) % MOD;
    }
    cout << ans << endn;
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    cin >> t;
    while (t --)
        solve();
    return 0;
}