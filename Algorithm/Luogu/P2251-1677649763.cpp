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
	int n, m;
	cin >> n >> m;

	vector<int> a(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> a[i];
	}

	deque<int> q;
	for (int i = 1; i < m; i ++) {
		while (!q.empty() && a[q.back()] > a[i]) {
			q.pop_back();
		}
		q.push_back(i);
	}
	vector<int> ret(n + 1);
	for (int i = m; i <= n; i ++) {
		while (!q.empty() && a[q.back()] > a[i]) q.pop_back();
		q.push_back(i);
		while (q.front() < i - m + 1) q.pop_front();
		ret[i] = a[q.front()];
	}
	for (int i = m; i <= n; i ++) {
		cout << ret[i] << '\n';
	}
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