#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)

using ll = long long;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    ll m;
    cin >> m;

    vector<ll>v(3);

    v[0] = 0, v[1] = 1;

    int n = 2, t = 2;
    for (;; n = (n + 1) % 3, t ++) {
        v[n] = (v[((n - 2) % 3 + 3) % 3] + v[((n - 1) % 3 + 3) % 3]) % m;
        if (v[n] % m == 1 && v[((n - 1) % 3 + 3) % 3] % m == 0)
            break;
    }

    cout << t - 1 << '\n';

    return 0;
}