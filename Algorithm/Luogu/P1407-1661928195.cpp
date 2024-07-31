#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Solution() {
	int n;
	cin >> n;
	vector<vector<int>> g(n * 2);
	auto add_edge = [&](int from, int to) {
		g[from].push_back(to);
	};
	vector<string> sv;
	vector<pair<string,string>> pv1(n);  // 夫妻之间婚姻
	for (auto &[a, b] : pv1) {
		cin >> a >> b;
		sv.emplace_back(a);
		sv.emplace_back(b);
	}
	// ranges::sort(sv);
	unordered_map<string,int> sid;  // string to vertex'id
	unordered_map<int,string> vid;  // vertex'id to string's index
	for (int i = 0; i < n * 2; ++ i) {
		sid[sv[i]] = i;
	}
	for (const auto &[a, b] : pv1) {
		add_edge(sid[a], sid[b]);
	}
 	int m;
	cin >> m;
	vector<pair<string,string>> pv2(m);  // 前任之间婚姻
	for (auto &[a, b] : pv2) {
		cin >> a >> b;
		add_edge(sid[b], sid[a]);
	}

	vector<int> dfn(n * 2, -1), low(n * 2, inf<int>), id(n * 2, -1);
	vector<bool> inst(n * 2);
	stack<int> st;
	vector<vector<int>> scc;
	int stamp = -1;
	function<void(int)> dfs = [&](int from) -> void {
		dfn[from] = low[from] = ++ stamp;
		inst[from] = true;
		st.emplace(from);
		for (auto to : g[from]) {
			if (dfn[to] == -1) {
				dfs(to);
				low[from] = min(low[from], low[to]);
			} else if (inst[to]) {
				low[from] = min(low[from], dfn[to]);
			}
		}
		if (dfn[from] == low[from]) {
			int now = 0, k = scc.size();
			scc.push_back({});
			do {
				now = st.top();
				st.pop();
				inst[now] = false;
				scc.back().push_back(now);
				id[now] = k;
			} while (now != from);
		}
	};
	for (int i = 0; i < 2 * n; ++ i) {
		if (dfn[i] == -1) {
			dfs(i);
		}
	}
	debug(sid);
	debug(id);
	for (const auto &[a, b] : pv1) {
		if (id[sid[a]] == id[sid[b]]) {
			cout << "Unsafe\n";
		} else {
			cout << "Safe\n";
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}