#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
#define cauto const auto
using LL = long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using ILL = __int128_t;

int n, m;

const int N = 1e6 + 10;
bool vis[N << 2];
vector<int>pri;
int f[N << 2];

void inti(){
    for (int i = 2; i <= m; ++ i){
        if (!vis[i])
            pri.push_back(i);
        for (int j = 0; j < pri.size(); ++ j){
            if (i * pri[j] > m)
                break;
            vis[i * pri[j]] = true;
            if (i % pri[j] == 0)
                break;
        }
        f[i] = pri.size();
    }
}

void solve(){
    int l, r;
    cin >> l >> r;
    if (l < 1 || r > m){
        cout << "Crossing the line\n";
        return;
    }
    cout << f[r] - f[l - 1] << '\n';
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    inti();
    while (n --){
        solve();
    }
    return 0;
}