/* P2835 刻录光盘 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

void Solution() {
	int n;
	cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n; ++ i) {
		int j;
		while (cin >> j && j != 0) {
			j --;
			g[i].push_back(j);
		} 
	}
	vector<int> dfn(n, -1), low(n, -1), id(n);
	int scc_cnt = -1, stamp = -1;
	vector<bool> inst(n, false);
	stack<int> st;
	function<void(int)> dfs = [&](int from) {
		debug(from);
		dfn[from] = low[from] = ++ stamp;
		st.push(from);
		inst[from] = true;
		for (int to : g[from]) {
			if (dfn[to] == -1) {
				dfs(to);
				low[from] = min(low[from], low[to]);
			} else if (inst[to]) {
				low[from] = min(low[from], dfn[to]);
			}
		}
		if (dfn[from] == low[from]) {
			int now = 0;
			++ scc_cnt;
			do {
				now = st.top();
				st.pop();
				inst[now] = false;
				id[now] = scc_cnt;
			} while (now != from);
		}
	};
	debug(1);
	for (int i = 0; i < n; ++ i) {
		if (dfn[i] == -1) {
			dfs(i);
		}
	}
	vector<vector<int>> G(scc_cnt + 1);
	for (int i = 0; i < n; ++ i) {
		for (int j : g[i]) {
			if (id[i] != id[j]) {
				G[id[i]].push_back(id[j]);
			}
		}
	}
	for (auto &i : G) {
		ranges::sort(i);
		i.erase(unique(i.begin(), i.end()), i.end());
	}
	vector<int> ind(scc_cnt + 1), outd(ind);
	for (int i = 0; i <= scc_cnt; ++ i) {
		for (auto j : G[i]) {
			ind[j] ++;
			outd[i] ++;
		}
	}
	cout << ranges::count(ind, 0) << '\n';
	// cout << min(ranges::count(ind, 0), ranges::count(outd, 0)) << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}