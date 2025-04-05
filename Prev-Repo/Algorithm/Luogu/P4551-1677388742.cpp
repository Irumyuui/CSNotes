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
	vector g(n + 1, vector<pair<int,int>>());
	for (int i = 1; i < n; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].emplace_back(v, w);
		g[v].emplace_back(u, w);
	}
	vector<int> dis(n + 1, -1);
	do {
		auto dfs = [&](auto &&dfs, int from) -> void {
			for (auto [to, w] : g[from]) {
				if (dis[to] == -1) {
					dis[to] = dis[from] ^ w;
					dfs(dfs, to);
				}
			}
		};
		dis[1] = 0;
		dfs(dfs, 1);
	} while (0);
	vector<array<int,2>> trie(1);
	trie.reserve(int(3e6 + 10));
	auto Insert = [&](int x) -> void {
		int p = 0;
		for (int i = 30; i >= 0; i --) {
			int d = (x >> i) & 1;
			if (trie[p][d] == 0) {
				trie[p][d] = trie.size();
				trie.push_back({});
			}
			p = trie[p][d];
		}
	};
	for (int i = 1; i <= n; i ++) {
		Insert(dis[i]);
	}
	auto Ask = [&](int x) -> int {
		int ret = 0, p = 0;
		for (int i = 30; i >= 0; i --) {
			int d = (x >> i) & 1;
			if (trie[p][!d]) {
				ret |= (1 << i);
				p = trie[p][!d];
			} else if (trie[p][d]) {
				p = trie[p][d];
			} else {
				break;
			}
		}
		return ret;
	};
	int ans = 0;
	for (int i = 1; i <= n; i ++) {
		ans = max(ans, Ask(dis[i]));
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