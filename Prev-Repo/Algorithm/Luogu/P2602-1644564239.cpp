#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll l, r;
ll c[18], ans[10], power10[17];

void solve(ll n, int ratio){
    int m = 0;

    while (n){
        c[++ m] = n % 10;
        n /= 10;
    }
    reverse(c + 1, c + 1 + m);

    for (int i = 1; i <= m; ++ i){
        for (int j = 1; j < i; ++ j){
            ans[c[j]] += ratio * c[i] * power10[m - i];
        }

        for (int j = 1; j < c[i]; ++ j){
            ans[j] += ratio * power10[m - i];
        }

        if (i != 1 && c[i]){
            ans[0] += ratio * power10[m - i];
        }

        if (i != m){
            for (int j = 1; j <= 9; ++ j){
                ans[j] += ratio * c[i] * (m - i) * power10[m - i - 1];
            }

            if (i != 1){
                ans[0] += ratio * (m - i) * c[i] * power10[m - i - 1] ;
            }
        }

        if (i == 1){
            if (m >= 2){
                ans[0] += ratio * (c[i] - 1) * (m - 1) * power10[m - 2] ;
            }

            for (int j = 2; j < m; ++ j){
                ans[0] += ratio * 9 * (m - j) * power10[m - j - 1];
            }
        }

        ans[c[i]] += ratio;

    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    power10[0] = 1;
    for (int i = 1; i < 17; ++ i){
        power10[i] = power10[i - 1] * 10;
    }

    cin >> l >> r;
    
    solve(r, 1);
    solve(l - 1, -1);

    for (const auto &res : ans){
        cout << res << ' ';
    }

    return 0;
}