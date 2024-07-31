/* P1726 上白泽慧音 */
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
		int from, to, t;
		cin >> from >> to >> t;
		from --, to --;
		g[from].push_back(to);
		if (t == 2) {
			g[to].push_back(from);
		}
	}

	vector<vector<int>> scc;
	int stamp = 0;
	vector<int> dfn(n, -1), low(dfn);
	vector<bool> inst(n);
	stack<int> st;
	function<void(int)> dfs = [&](int from) {
		dfn[from] = low[from] = ++ stamp;
		inst[from] = true;
		st.push(from);
		for (auto to : g[from]) {
			if (dfn[to] == -1) {
				dfs(to);
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
			sort(scc.back().begin(), scc.back().end());
		}
	};
	for (int i = 0; i < n; ++ i) {
		if (dfn[i] == -1) {
			dfs(i);
		}
	}

	sort(scc.begin(), scc.end(), [](const auto &a, const auto &b) {
		if (a.size() != b.size()) {
			return a.size() > b.size();
		}
		return a > b;
	});
	cout << scc.front().size() << '\n';
	for (auto &x : scc.front()) {
		cout << x + 1 << ' ';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}