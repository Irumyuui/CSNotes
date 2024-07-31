/* P3382 【模板】三分法 */
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

template <typename T> constexpr T qp(T a, long long i) {
	T ret = T{1};
	for (; i > 0; i >>= 1, a *= a)
		if (i & 1) 
			ret *= a;
	return ret;
}

void Solution() {
	int n; ld l, r;
	cin >> n >> l >> r;
	vector<ld> a(n + 1);
	for (auto &x : a) {
		cin >> x;
	}
	std::ranges::reverse(a);

	auto calc = [&](ld d) {
		ld ret = 0;
		for (int i = 0; i <= n; i ++) {
			ret += a[i] * qp(d, i);
		}
		return ret;
	};
	
	for (int i = 1000; i; i --) {
		ld mid = midpoint(l, r);
		ld lmid = midpoint(l, mid), rmid = midpoint(mid, r);
		if (calc(lmid) > calc(rmid)) {
			r = rmid;
		} else {
			l = lmid;
		}
	}
	cout << r << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}