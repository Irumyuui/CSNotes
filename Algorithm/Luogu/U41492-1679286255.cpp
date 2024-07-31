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
	namespace rgs = std::ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

auto Main() -> void {
	int n;
	cin >> n;
	
	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}
	vector<set<int>> f(n + 1);
	for (int i = 1; i <= n; i ++) {
		int x;
		cin >> x;
		f[i].emplace(x);
	}

	vector<int> cnt(n + 1);
	auto dfs = [&](auto &&dfs, int from, int come) -> void {
		for (auto to : adj[from]) {
			if (to != come) {
				dfs(dfs, to, from);
				if (f[from].size() < f[to].size()) {
					swap(f[from], f[to]);
				}
				for (auto x : f[to]) {
					f[from].emplace(x);
				}
			}
		}
		cnt[from] = f[from].size();
	};
	dfs(dfs, 1, 0);

	int q;
	cin >> q;
	for (int _ = 1; _ <= q; _ ++) {
		int x;
		cin >> x;
		cout << cnt[x] << '\n';
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Main();
	}
}