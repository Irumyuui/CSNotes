#include <bits/stdc++.h>

namespace prime{
    using ll = long long;
    
    ll mul(ll a, ll b, ll m){
        return static_cast<__int128>(a) * b % m;
    }
    
    ll power(ll a, ll i, ll m){
        ll res = 1 % m;
        while (i){
            if (i & 1)
                res = mul(res, a, m);
            a = mul(a, a, m);
            i >>= 1;
        }
        return res;
    }
    
    bool isprime(ll n){
        if (n < 2){
            return false;
        }
        
        static constexpr int _[] = {2, 3, 5, 7, 9, 11, 17, 19, 23};
        int s = __builtin_ctzll(n - 1);
        ll d = (n - 1) >> s;
        
        for (const auto &__ : _){
            if (__ == n){
                return true;
            }
            
            ll x = power(__, d, n);
            if (x == 1 || x == n - 1){
                continue;
            }
            
            bool ok = false;
            for (int i = 0; i < s - 1; ++ i){
                x = mul(x, x, n);
                if (x == n - 1){
                    ok = true;
                    break;
                }
            }
            
            if (!ok){
                return false;
            }
        }
        return true;
    }

}

using prime::isprime;
using namespace std;

using ll = long long;
int c[100];
template<typename T = long long> inline bool isright(T n){
    int m = 0;
    while (n){
        c[++ m] = n % 10;
        n /= 10;
    }

    for (int i = 1, j = m; i < j; ++ i, -- j){
        if (c[i] != c[j]){
            return false;
        }
    }
    return true;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    ll l, r;
    cin >> l >> r;

    for (ll i = l & 1 ? l : l + 1; i <= r; i += 2){
        if (isright(i) && isprime(i)){
            cout << i << '\n';
        }
    }

    return 0;
}