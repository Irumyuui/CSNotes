#include <bits/stdc++.h>
using ll = long long;

std::tuple<ll, ll, ll> exgcd(ll a, ll b) {
    if (b == 0)
        return {a, 1, 0};
    auto [d, x, y] = exgcd(b, a % b);
    return {d, y, x - a / b * y};
}

inline ll mul(ll a, ll b, ll p) {
    a = (a % p + p) % p;
    b = (b % p + p) % p;
    ll d = static_cast<long double>(a) * b / p;
    d = a * b - d * p;
    if (d < 0)
        d += p;
    if (d > p)
        d -= p;
    return d;
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

const int MAXN = 1e7 + 10;
int phi[MAXN];
std::vector<ll> prime;
// std::vector<bool>vis;
bool vis[MAXN];

long long work(long long n) {
    if (n == 1) {
        return 0;
    }
    return power(2, work(phi[n]) + phi[n], n);
}

void solve() {
    ll p;
    std::cin >> p;
    std::cout << work(p) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    phi[1] = 1;
    for (int i = 2; i <= 1e7; ++ i) {
        if (!vis[i]) {
            prime.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; prime[j] * i <= 1e7; ++ j) {
            vis[prime[j] * i] = true;
            if (i % prime[j] != 0) {
                phi[i * prime[j]] = phi[i] * phi[prime[j]];
            } else {
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
        }
    }

    int t;
    std::cin >> t;
    while (t --) {
        solve();
    }

    return 0;
}