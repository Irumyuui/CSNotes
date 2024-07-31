#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include "debug.hpp"
#else
	#define debug(...)
#endif

using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = int64_t;
using ld = long double;

void Main() {
	int n;
	cin >> n;
	
	vector<int> dad(n, -1);
	auto Find = [&](auto &&self, int x) -> int {
		if (dad[x] == -1) {
			return x;
		}
		return dad[x] = self(self, dad[x]);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b) {
			return false;
		}
		dad[a] = b;
		return true;
	};

	vector<i64> vw(n);
	for (auto &x : vw) {
		cin >> x;
	}

	int a = -1, b = -1;
	vector adj(n, vector<int>{});
	for (int i = 0; i < n; i ++) {
		int u, v;
		cin >> u >> v;
		if (Merge(u, v)) {
			adj[u].emplace_back(v);
			adj[v].emplace_back(u);
		} else {
			a = u; b = v;
		}
	}

	assert(a != -1 & b != -1);
	debug(a, b);

	vector<array<i64, 2>> f(n);
	auto dfs = [&](auto &&dfs, int from, int come) -> void {
		f[from] = {0, vw[from]};
		for (auto to : adj[from]) {
			if (come != to) {
				dfs(dfs, to, from);
				f[from][0] += ranges::max(f[to]);
				f[from][1] += f[to][0];
			}
		}
	};

	i64 tmp = vw[a];
	vw[a] = -inf<i64>;
	dfs(dfs, b, -1);
	i64 ret = ranges::max(f[b]);
	vw[a] = tmp;

	debug(f[b]);	
	
	tmp = vw[b];
	vw[b] = -inf<i64>;
	dfs(dfs, a, -1);
	ret = max({ret, f[a][0], f[a][1]});
	vw[b] = tmp;

	debug(f[a]);

	ld k;
	cin >> k;
	cout << fixed << setprecision(1) << k * ret << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}