#include <bits/stdc++.h>
using namespace std;
#define all(X) begin(X), end(X)
#define cauto const auto

using ll = long long;
using LL = __int128_t;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    if (n == 1) {
        cout << 0;
        return 0;
    }

    vector<int>phi(n << 1, 0), f(n << 1, 0);

    phi[1] = 1;
    for (int i = 1; i <= n; ++ i) {
        if (!phi[i]) {
            for (int j = i; j <= n; j += i) {
                if (!phi[j]) {
                    phi[j] = j;
                }
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }

    for (int i = 1; i <= n; ++ i) {
        f[i] =  f[i - 1] + phi[i];
    }

    cout << f[n - 1] * 2 + 1;
    
    return 0;
}