#include <bits/stdc++.h>
using namespace std;

const int N = 510;

void Main() {
	int m;
	cin >> m;

	vector adj(N, vector<pair<int,int>>());
	vector deg(N, 0);
	for (int i = 0; i < m; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
		deg[u] ++; deg[v] ++;
	}

	for (auto &vec : adj) {
		ranges::sort(vec);
	}

	int odd = ranges::count_if(deg, [](const auto &deg) {
		return deg % 2 != 0;
	});
	
	vector<int> ret;
	vector<int> vis(m);
	auto dfs = [&](auto &&dfs, int from) -> void {
		for (auto [to, eid] : adj[from]) {
			if (!vis[eid]) {
				vis[eid] = true;
				dfs(dfs, to);
			}
		}
		ret.emplace_back(from);
	};

	for (int i = 0; i < N; i ++) {
		if (deg[i]) {
			if (odd && !(deg[i] % 2)) {
				continue;
			}
			dfs(dfs, i);
			for (auto x : ret | views::reverse) {
				cout << x << '\n';
			}
			return;
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}