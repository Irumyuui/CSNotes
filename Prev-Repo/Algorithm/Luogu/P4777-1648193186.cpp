#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ill = __int128_t;

tuple<ll, ll, ll> exgcd(ll a, ll b) {
    if (b == 0)
        return {a, 1, 0};
    auto [d, x, y] = exgcd(b, a % b);
    return {d, y, x - a / b * y};
}

// inline ll mul(ll a, ll b, ll p) {
//     return static_cast<__int128_t>(a) * b % p;
// }

inline ll mul(ll a, ll b, ll p) {
    a = (a % p + p) % p;
    b = (b % p + p) % p;
    ll d = static_cast<long double>(a) * b / p;
    d = a * b - d * p;
    if (d >= p)
        d -= p;
    if (d < 0)
        d += p;
    return d;
}

bool merge(ll &a, ll &b, ll c, ll d) {
    auto [g, t0, no] = exgcd(b, d);
    if ((c - a) % g != 0) 
        return false;
    d /= g;
    ll t = mul((c - a) / g, t0, d);
    if (t < 0)
        t += d;
    a = b * t + a;
    b = b * d;
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    ll a = 0, b = 1;
    for (int i = 0; i < n; ++ i) {
        ll c, d;
        cin >> d >> c;
        merge(a, b, c, d);   
    }
    cout << a << '\n';

    return 0;
}