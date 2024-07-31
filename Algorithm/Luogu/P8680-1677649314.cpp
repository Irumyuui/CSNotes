#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

auto Solve() -> void {
	int n;
	cin >> n;
	auto check = [](int x) {
		while (x > 0) {
			int t = x % 10;
			if (t == 2 || t == 0 || t == 1 || t == 9) {
				return true;
			}
			x /= 10;
		}
		return false;
	};
	ll ret = 0;
	for (int i = 1; i <= n; i ++) {
		if (check(i)) {
			ret += i;
		}
	}
	cout << ret << '\n';
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}