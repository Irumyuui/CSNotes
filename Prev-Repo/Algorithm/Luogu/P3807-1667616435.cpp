#include <bits/stdc++.h>

using ll = long long;

ll add(ll a, ll b, ll p) {
	return (a + b) % p;
}
ll mul(ll a, ll b, ll p) {
	return a * b % p;
}
std::array<ll,3> exgcd(ll a, ll b) {
	if (b == 0) {
		return {a, 1, 0};
	} else {
		auto [d, x, y] = exgcd(b, a % b);
		return {d, y, x - a / b * y};
	}
}
ll inv(ll a, ll p) {
	auto [d, x, _] = exgcd(a, p);
	if (x < 0) {
		x += p;
	}
	if (x >= p) {
		x -= p;
	}
	return x;
}
ll binom(int n, int m, ll p) {
	ll a = 1, b = 1;
	for (ll i = n, j = m; i > (n - m); i --, j --) {
		a = mul(a, i, p);
		b = mul(b, j, p);
	}
	return mul(a, inv(b, p), p);
}

ll lucas(ll n, ll m, ll p) {
	if (n == 0) {
		return 1;
	}
	return mul(binom(n % p, m % p, p), lucas(n / p, m / p, p), p);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t --) {
		ll n, m, p;
		std::cin >> n >> m >> p;
		std::cout << lucas(n + m, n, p) << '\n';
	}
}