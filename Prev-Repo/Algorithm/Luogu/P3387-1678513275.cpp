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
	
	vector<ll> vw(n + 1);
	for (int i = 1; i <= n; i ++) {
		cin >> vw[i];
	}
	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= m; i ++) {
		int from, to;
		cin >> from >> to;
		adj[from].emplace_back(to);
	}

	vector<int> dfn(n + 1, -1), low(n + 1), scc_id(n + 1);
	vector<bool> inst(n + 1);
	stack<int> st;
	int stamp = 0, scc_cnt = 0;
	auto dfs = [&](auto &&dfs, int from) -> void {
		dfn[from] = low[from] = ++ stamp;
		st.emplace(from);
		inst[from] = true;

		for (auto to : adj[from]) {
			if (dfn[to] == -1) {
				dfs(dfs, to);
				low[from] = min(low[from], low[to]);
			} else if (inst[to]) {
				low[from] = min(low[from], dfn[to]);
			}
		}

		if (dfn[from] == low[from]) {
			int v;
			scc_cnt ++;
			do {
				v = st.top();
				st.pop();
				inst[v] = false;
				scc_id[v] = scc_cnt;
			} while (v != from);
		}
	};
	for (int i = 1; i <= n; i ++) {
		if (dfn[i] == -1) {
			dfs(dfs, i);
		}
	}

	vector scc_adj(scc_cnt + 1, vector<int>());
	vector<ll> scc_vw(scc_cnt + 1);
	for (int i = 1; i <= n; i ++) {
		scc_vw[scc_id[i]] += vw[i];
		for (auto j : adj[i]) {
			if (scc_id[i] != scc_id[j]) {
				scc_adj[scc_id[i]].emplace_back(scc_id[j]);
			}
		}
	}
	for (auto &v : scc_adj) {
		rgs::sort(v);
		v.erase(unique(v.begin(), v.end()), v.end());
	}

	vector<int> scc_ind(scc_cnt + 1);
	for (int i = 1; i <= scc_cnt; i ++) {
		for (int j : scc_adj[i]) {
			scc_ind[j] ++;
		}
	}

	vector<ll> f(scc_cnt + 1);
	queue<int> q;
	for (int i = 1; i <= scc_cnt; i ++) {
		if (!scc_ind[i]) {
			q.emplace(i);
		}
	}
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		f[from] += scc_vw[from];
		for (auto to : scc_adj[from]) {
			f[to] = max(f[to], f[from]);
			if (-- scc_ind[to] == 0) {
				q.emplace(to);
			}
		}
	}

	cout << rgs::max(f) << '\n';
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