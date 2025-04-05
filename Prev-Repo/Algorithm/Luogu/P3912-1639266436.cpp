#include <bits/stdc++.h>
using namespace std;

int n;
vector<bool>num;
vector<int>prime;

void solve(){
    cin >> n;
    num = vector<bool>(n + 1, false);
    for (int i = 2; i <= n; ++ i){
        if (!num[i]) prime.push_back(i);
        for (int j = 0; prime[j] <= n / i; ++ j){
            num[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
    cout << prime.size() << endl;
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}