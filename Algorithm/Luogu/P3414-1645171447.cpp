#include <bits/stdc++.h>

using ll = long long;

inline ll mul(ll a, ll b, ll p) {
    return static_cast<__int128_t>(a) * b % p;
}

inline ll power(ll a, ll i, ll p) {
    ll res = 1 % p;
    while (i) {
        if (i & 1) {
            res = mul(res, a, p);
        }
        a = mul(a, a, p);
        i >>= 1;
    }
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll p = 6662333;

    ll n;
    std::cin >> n;

    std::cout << power(2, n - 1, p) << '\n';

    return 0;
}