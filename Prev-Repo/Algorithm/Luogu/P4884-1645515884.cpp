#include <bits/stdc++.h>

#define all(container) std::begin(container), std::end(container)
#define range(iterator, container) for (auto &iterator : container)
#define crange(iterator, container) for (const auto &iterator : container)
#define cauto const auto
#define clear(array) std::memset(array, 0, sizeof(array))

using ll = long long;
using LL = __int128_t;

inline ll mul(ll a, ll b, ll p) {
    return static_cast<__int128_t>(a) * b % p;
}

inline ll power(ll a, ll i, ll p) {
    ll res = 1 % p;
    while (i) {
        if (i & 1)
            res = mul(res, a, p);
        a = mul(a, a, p);
        i >>= 1;
    }
    return res;
}

inline ll BSGS(ll a, ll b, ll p) {
    if (a % p == 0) {
        if (b % p == 0) {
            return 1;
        }
        return -1;
    }

    std::unordered_map<ll, ll>right;

    ll t = std::ceil(std::sqrt(p));

    for (ll B = 0; B < t; ++ B) {
        right[ mul(b, power(a, B, p), p) ] = B;
    }

    for (ll A = 0; A <= t; ++ A) {
        ll left = power(a, A * t, p);
        
        if (right.find(left) != right.end()) {
            ll ans = A * t - right[left];
            if (ans >= 0) {
                return ans;
            }
        }
    }

    return -1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    ll K, m;
    std::cin >> K >> m;

    K = (K * 9 + 1) % m;

    std::cout << BSGS(10, K, m) << '\n';

    return 0;
}