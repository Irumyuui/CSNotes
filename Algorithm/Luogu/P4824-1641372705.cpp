#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 2e6 + 10;
char str[LEN], t[LEN];
int ans[LEN], nex[LEN], snex[LEN], sl, tl, p;

void solve(){
    cin >> str + 1 >> t + 1;
    sl = strlen(str + 1);
    tl = strlen(t + 1);
    for (int i = 2, k = nex[0] = nex[1] = 0; i <= sl; ++ i){
        while (k && t[k + 1] != t[i])
            k = nex[k];
        if (t[k + 1] == t[i])
            k ++;
        nex[i] = k;
    }
    p = 0;
    for (int i = 1, k = 0; i <= sl; ++ i){
        while (k && str[i] != t[k + 1])
            k = nex[k];
        if (str[i] == t[k + 1])
            k ++;
        snex[i] = k;
        ans[++ p] = i;
        if (tl == k){
            p -= tl;
            k = snex[ans[p]];
        }
    }
    for (int i = 1; i <= p; ++ i){
        cout << str[ans[i]] ;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    solve();
    return 0;
}