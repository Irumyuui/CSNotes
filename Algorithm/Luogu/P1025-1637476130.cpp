#include <bits/stdc++.h>
using namespace std;
int n, k, ans;

void dfs(int pos, int num, int cnt){
    if (cnt == 1){
        ans ++;
        return;
    }
    for (int i = pos; i <= num / cnt; ++ i){
        dfs(i, num - i, cnt - 1);
    }
    return;
}

void solve(){
    cin >> n >> k;
    dfs(1, n, k);
    cout << ans << endl;
    return;
}

int main(){
    // FREIN("in.in");
    solve();
    return 0;
}