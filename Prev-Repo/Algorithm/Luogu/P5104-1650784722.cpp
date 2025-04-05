#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)
using ll = long long;
tuple<ll, ll, ll> exgcd(ll a, ll b) {
    if (b == 0) return {a, 1, 0};
    auto [d, x, y] = exgcd(b, a % b);
    return {d, y, x - a / b * y};
}
ll inv(ll n, ll p) {
    auto [_, x, __] = exgcd(n, p);
    return (x % p + p) % p;
}
ll mul(ll a, ll b, ll p) {
    return static_cast<__int128_t>(a) * b % p;
}
ll pow(ll a, ll i, ll p) {
    ll res = 1 % p;
    for (; i; i >>= 1, a = mul(a, a, p)) {
        if (i & 1)
            res = mul(res, a, p);
    }
    return res;
}
const ll MOD = 1e9 + 7;

signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    ll w, n, k;
    cin >> w >> n >> k;
    ll t = pow(2, k, MOD);
    t = inv(t, MOD);
    cout << w * t % MOD << '\n';

    return 0;
}