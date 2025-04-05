/* P2863 [USACO06JAN]The Cow Prom S */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES cout << "YES\n"
#define NO cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

void Solution() {
	int n, m;
	cin >> n >> m;
	vector g(n, vector<int>());
	for (int i = 0; i < m; ++ i) {
		int from, to;
		cin >> from >> to;
		from --;
		to --;
		g[from].push_back(to);
	}

	vector<bool> inst(n);
	stack<int> st;
	vector<int> dfn(n, -1), low(dfn);
	int stamp = 0;
	vector<vector<int>> scc;
	function<void(int)> tarjan = [&](int from) {
		dfn[from] = low[from] = ++ stamp;
		inst[from] = true;
		st.push(from);
		for (auto to : g[from]) {
			if (dfn[to] == -1) {
				tarjan(to);
				low[from] = min(low[from], low[to]);
			} else if (inst[to]) {
				low[from] = min(low[from], dfn[to]);
			}
		}
		if (dfn[from] == low[from]) {
			scc.push_back({});
			int now = 0;
			do {
				now = st.top();
				st.pop();
				inst[now] = false;
				scc.back().push_back(now);
			} while (now != from);
		}
	};
	for (int i = 0; i < n; ++ i) {
		if (dfn[i] == -1) {
			tarjan(i);
		}
	}

	debug(scc);

	int ans = 0;
	for (auto &x : scc) {
		if (x.size() > 1) {
			ans ++;
		}
	}
	cout << ans << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}