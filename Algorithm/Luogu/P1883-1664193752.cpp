/* P1883 函数 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;
using ld = long double;

void Solution() {
	int n;
	cin >> n;
	vector<array<ld,3>> a(n);	
	for (auto &x : a) {
		cin >> x[0] >> x[1] >> x[2];
	}
	
	ld ans = inf<ld>;

	auto calc = [&](ld x) {
		ld ret = -inf<ld>;
		for (auto &[a, b, c] : a) {
			ret = max({
				ret, x * x * a + x * b + c
			});
		}
		ans = min(ans, ret);
		return ret;
	};

	ld l = 0, r = 1000;
	while (r - l >= 1e-10L) {
		ld lmid = l + (r - l) / 3, rmid = l + (r - l) / 3 * 2;
		if (calc(lmid) < calc(rmid)) {
			r = rmid;
		} else {
			l = lmid;
		}
	}
	cout << ans << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(4);
	int t; std::cin >> t; while (t --> 0)
		Solution();
}