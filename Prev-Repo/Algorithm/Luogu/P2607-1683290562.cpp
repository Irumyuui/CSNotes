#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include "debug.hpp"
#else
	#define debug(...)
#endif
using namespace std;
#if __cplusplus >= 202002L
	namespace rgs = std::ranges;
#endif
template <typename _Tp, typename _Cmp = std::greater<_Tp>, typename _Seq = std::vector<_Tp>>
using PriorityQueue = std::priority_queue<_Tp, _Seq, _Cmp>;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using i64 = int64_t;

void Main() {
	int n;
	cin >> n;
	
	vector<int> dad(n + 1, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1) {
			return x;
		}
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) -> bool {
		a = Find(Find, a);
		b = Find(Find, b);
		if (a == b) {
			return false;
		}
		dad[a] = b;
		return true;
	};

	vector<i64> vw(n + 1);
	vector adj(n + 1, vector<int>());
	vector<pair<int,int>> loop;
	for (int i = 1; i <= n; i ++) {
		i64 w;
		int x;
		cin >> w >> x;
		vw[i] = w;
		if (Merge(i, x)) {
			adj[i].emplace_back(x);
			adj[x].emplace_back(i);
		} else {	
			loop.emplace_back(x, i);
		}
	}

	debug(adj);

	vector<array<i64,2>> f(n + 1);
	vector<bool> vis(n + 1);
	auto dfs = [&](auto &&dfs, int from, int come) -> void {
		debug(from, come);
		vis[from] = true;
		f[from] = {0, vw[from]};
		for (auto to : adj[from]) {
			if (to == come)
				continue;
			dfs(dfs, to, from);
			f[from][0] += ranges::max(f[to]);
			f[from][1] += f[to][0];
		}
	};

	i64 ret = 0;
	for (auto [a, b] : loop) {
		auto work = [&](int a, int b) -> i64 {
			auto tmp = vw[a];
			vw[a] = -inf<i64>;
			dfs(dfs, b, -1);
			i64 ret = ranges::max(f[b]);
			vw[a] = tmp;
			return ret;
		};
		ret += max(work(a, b), work(b, a));
	}

	for (int i = 1; i <= n; i ++) {
		if (!vis[i]) {
			dfs(dfs, i, -1);
			ret += ranges::max(f[i]);
		}
	}

	cout << ret << '\n';
}

std::int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test);
		Main();
	}
}