#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

void Main() {
	int n;
	cin >> n;

	vector<int> dad(1 << 8, -1);
	auto Find = [&](auto &&Find, int x) -> int {
		if (dad[x] == -1)
			return x;
		return dad[x] = Find(Find, dad[x]);
	};
	auto Merge = [&](int a, int b) {
		a = Find(Find, a); b = Find(Find, b);
		if (a == b)
			return false;
		dad[a] = b;
		return true;
	};
	
	vector<bool> have(1 << 8);
	vector adj(1 << 8, vector<int>());
	vector<int> deg(1 << 8);
	for (int i = 0; i < n; i ++) {
		char u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
		deg[u] ++; deg[v] ++;
		have[u] = have[v] = true;
		Merge(u, v);
	}

	int les = 0;
	bool one = false;
	for (int i = 0; i < (1 << 8); i ++)
		les += have[i] && dad[i] == -1;
	if (les != 1) {
		cout << "No Solution\n";
		return;
	} else if (int cnt = ranges::count_if(deg, [](const auto &x) {
		return x % 2 != 0;
	}); cnt != 0 && cnt != 2) {
		cout << "No Solution\n";
		return;
	} else if (cnt == 2) {
		one = true;
	}

	for (auto &v : adj) {
		ranges::sort(v, [](const auto &a, const auto &b) {
			return a < b;
		});
	}
	
	set<pair<int,int>> vis;
	vector<char> ret;
	auto dfs = [&](auto &&dfs, int from) -> void {
		for (auto to : adj[from]) {
			if (!vis.contains(pair{from, to})) {
				vis.emplace(from, to);
				vis.emplace(to, from);
				dfs(dfs, to);
			}
		}
		ret.emplace_back(from);
	};
	for (int i = 0; i < (1 << 8); i ++) {
		if (have[i]) {
			if (one) {
				if (deg[i] % 2) 
					dfs(dfs, i);
				else
					continue;
			} else {
				dfs(dfs, i);
			}
			for (auto x : ret | views::reverse) {
				cout << x;
			}
			cout << '\n';
			return;
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}