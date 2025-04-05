#include <bits/stdc++.h>

template<typename T> inline T mul(T a, T b, T p) {
    return static_cast<__int128_t>(a) * b % p;
}

template<typename T> inline T power(T a, T i, T p) {
    T res = 1 % p;
    while (i) {
        if (i & 1) {
            res = mul(res, a, p);
        }
        a = mul(a, a, p);
        i >>= 1;
    }
    return res;
}

using ll = long long;

inline ll BSGS(ll a, ll b, ll p) {
    b %= p;

    std::unordered_map<ll, ll>Bi;

    ll t = std::sqrt(p) + 1;

    for (ll B = 0; B < t; ++ B) {
        Bi[mul(b, power(a, B, p), p)] = B;
    }

    ll at = power(a, t, p);
    for (ll A = 0; A < t; ++ A) {
        ll atA = power(at, A, p);
        if (Bi.count(atA)) {
            ll ans = A * t - Bi[atA];
            if (ans >= 0) {
                return ans;
            }
        }
    }

    return -1;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll a, b, p;
    std::cin >> p >> a >> b;

    ll ans = BSGS(a, b, p);

    if (ans != -1) {
        std::cout << ans << '\n';
    } else {
        std::cout << "no solution\n";
    }

    return 0;
}