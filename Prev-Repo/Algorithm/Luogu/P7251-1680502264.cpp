#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, m;
	cin >> n >> m;

	vector adj(n + 1, vector<int>());
	for (int i = 0; i < m; i ++) {
		int from, to;
		cin >> from >> to;
		adj[from].emplace_back(to);
	}

	vector<int> dfn(n + 1, -1), low(n + 1, -1), scc_id(n + 1, -1);
	vector<bool> inst(n + 1);
	vector<int> stk;
	int scc_cnt = 0, stamp = 0;
	auto dfs = [&](auto &&dfs, int from) -> void {
		dfn[from] = low[from] = ++ stamp;
		stk.emplace_back(from);
		inst[from] = true;
		for (auto to : adj[from]) {
			if (dfn[to] == -1) {
				dfs(dfs, to);
				low[from] = min(low[from], low[to]);
			} else if (inst[to]) {
				low[from] = min(low[from], dfn[to]);
			}
		}
		if (low[from] == dfn[from]) {
			int now = 0;
			++ scc_cnt;
			do {
				now = stk.back();
				stk.pop_back();
				inst[now] = false;
				scc_id[now] = scc_cnt;
			} while (now != from);
		}
	};
	for (int i = 1; i <= n; i ++) {
		if (dfn[i] == -1) {
			dfs(dfs, i);
		}
	}

	vector scc_adj(scc_cnt + 1, vector<int>());
	vector<int> scc_vcnt(scc_cnt + 1);
	for (int from = 1; from <= n; from ++) {
		scc_vcnt[scc_id[from]] ++;
		for (auto to : adj[from]) {
			if (scc_id[from] != scc_id[to]) {
				scc_adj[scc_id[from]].emplace_back(scc_id[to]);
			}
		}
	}
	for (auto &v : scc_adj | std::views::drop(1)) {
		std::ranges::sort(v);
		v.erase(unique(v.begin(), v.end()), v.end());
	}
	
	vector<int> ind(scc_cnt + 1), outd(scc_cnt + 1);
	for (int from = 1; from <= scc_cnt; from ++) {
		for (auto to : scc_adj[from]) {
			ind[to] ++;
		}
		outd[from] = scc_adj[from].size();
	}
	
	cout << std::ranges::max(scc_vcnt | std::views::drop(1)) << '\n';
	if (scc_cnt == 1) {
		cout << 0 << '\n';
	} else {
		cout << std::max(
			std::ranges::count(ind | std::views::drop(1), 0),
			std::ranges::count(outd | std::views::drop(1), 0)
		) << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}