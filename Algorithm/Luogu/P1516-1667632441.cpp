#include <bits/stdc++.h>

using ll = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	auto exgcd = [](auto &&exgcd, ll a, ll b) -> std::array<ll,3> {
		if (b == 0) {
			return {a, 1, 0};
		} else {
			auto [d, x, y] = exgcd(exgcd, b, a % b);
			return {d, y, x - a / b * y};
		}
	};
	ll x, y, m, n, l;
	std::cin >> x >> y >> m >> n >> l;
	ll a = n - m, b = l, c = x - y;
	if (a < 0) {
		a = -a; c = -c;
	}
	auto [d, x0, y0] = exgcd(exgcd, a, b);
	if (c % d != 0) {
		std::cout << "Impossible\n";
	} else {
		std::cout << (x0 * (c / d) % (b / d) + (b / d)) % (b / d) << '\n';
	}
}