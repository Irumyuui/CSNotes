#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
#define cauto const auto

using ll = long long;
using LL = __int128_t;

const int MAXN = 1e7 + 10;
int dad[MAXN];

int Find(int self, int &cnt) {
    ++ cnt;
    if (dad[self] != -1) {
        return Find(dad[self], cnt);
    }
    return self;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    fill(dad, dad + 1 + n, -1);

    int ans = 1 << 30;
    for (int i = 1; i <= n; ++ i) {
        int to;
        cin >> to;
        
        int cnt = 0;
        int todad = Find(to, cnt);

        if (todad == i) {
            ans = min(ans, cnt);
        } else {
            dad[i] = to;
        }
    }

    cout << ans << '\n';

    return 0;
}