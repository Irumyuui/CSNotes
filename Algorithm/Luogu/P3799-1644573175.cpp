#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll MOD = 1e9 + 7;
ll cnt[int(5e6 + 10)];

inline __int128_t C2(ll n){
    return static_cast<__int128>(n) * (n - 1) / 2;
}

int main(){
    std::ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    for (int i = 0, x; i < n; ++ i){
        cin >> x;
        cnt[x] ++;
    }

    ll ans = 0;
    for (int i = 1; i <= 5000; ++ i){
        if (!cnt[i]){
            continue;
        }

        for (int j = i; j <= 5000; ++ j){
            if (!cnt[j]){
                continue;
            }
            if (cnt[i + j] < 2){
                continue;
            }
            if (j == i){
                if (cnt[i] == 1){
                    continue;
                }
                ans += C2(cnt[i]) * C2(cnt[i + j]) % MOD;
            }else{
                ans += cnt[i] * cnt[j] * C2(cnt[i + j]) % MOD;
            }
            ans %= MOD;
        }
    }

    cout << ans << '\n';

    return 0;
}