#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
namespace rgs = ranges;
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

template <typename T>
auto operator >> (istream &in, std::vector<T> &v) -> std::istream& {
	for (auto &&i : v) in >> i;
	return in;
}
template <typename T>
auto operator << (ostream &out, std::vector<T> &v) -> std::ostream& {
	for (int32_t i = 0, n = v.size(); i < n; i += 1) {
		if (i != 0) out << ' ';
		out << v[i];
	}
	return out;
}

auto Solve() -> void {
	int n, m;
	cin >> n >> m;
	vector<pair<int,int>> edge(m);
	vector<int> deg(n);
	for (auto &[u,v] : edge) {
		cin >> u >> v;
		u --, v --;
		deg[u] ++, deg[v] ++;
	}
	vector g(n, vector<int>());
	for (auto [u,v] : edge) {
		if (deg[u] > deg[v]) {
			g[u].emplace_back(v);
		} else if (deg[u] < deg[v]) {
			g[v].emplace_back(u);
		} else {
			g[min(u,v)].emplace_back(max(u,v));
		}
	}
	ll ans = {};
	for (int i = 0; i < n; i ++) {
		vector<bool> tod(n);
		for (auto j : g[i])
			tod[j] = true;
		for (auto j : g[i])
			for (auto k : g[j]) 
				ans += tod[k];
	}
	cout << ans << '\n';
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