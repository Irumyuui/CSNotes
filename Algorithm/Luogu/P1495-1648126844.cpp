#include <bits/stdc++.h>
using namespace std;
using ll = long long;

tuple<ll, ll, ll> exgcd(ll a, ll b) {
    if (b == 0) 
        return {a, 1, 0};
    auto [d, x, y] = exgcd(b, a % b);
    return {d, y, x - a / b * y};
}

bool merge(ll &a, ll &b, ll c, ll d) {
    auto [g, t0, _] = exgcd(b, d);
    if ((c - a) % g != 0)
        return false;
    d /= g;
    ll t = (c - a) / g % d * t0  % d;
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
        cin >> c >> d;
        merge(a, b, d, c);
    }
    cout << a << '\n';

    return 0;
}