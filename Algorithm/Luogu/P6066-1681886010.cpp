#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, m;
	cin >> n >> m;

	vector adj(n, vector<pair<int,int>>());
	for (int i = 0; i < m; i ++) {
		int u, v;
		cin >> u >> v;
		u --; v --;
		adj[u].emplace_back(v, i * 2);
		adj[v].emplace_back(u, i * 2 + 1);
	}

	vector<bool> vis(m * 2);
	vector<int> ret;
	auto dfs = [&](auto &&dfs, int from) -> void {
		for (auto [to, id] : adj[from]) {
			if (!vis[id]) {
				vis[id] = true;
				dfs(dfs, to);
			}
		}
		ret.emplace_back(from);
	};
	dfs(dfs, 0);

	for (auto x : ret | views::reverse | views::transform([](int x) { return x + 1; })) {
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}