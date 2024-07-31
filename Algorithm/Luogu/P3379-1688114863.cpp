#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, q, root;
	cin >> n >> q >> root;

	vector adj(n + 1, vector<int>{});
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	vector<int> edfn{0}, dfn(n + 1), dep(n + 1, -1);
	edfn.reserve(n * 2 + 1);
	auto dfs = [&](auto &&dfs, int from) mutable -> void {
		dfn[from] = edfn.size();
		edfn.emplace_back(from);
		for (auto to : adj[from]) {
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				dfs(dfs, to);
				edfn.emplace_back(from);
			}
		}
	};
	dep[root] = 0;
	dfs(dfs, root);

	int nn = edfn.size() - 1;
	vector f(std::__lg(nn) + 1, vector<int>(nn + 1));
	for (int i = 1; i <= nn; i ++) {
		f[0][i] = edfn[i];
	}
	for (int i = 1; i <= __lg(nn); i ++) {
		for (int j = 1; j + (1 << i) <= nn; j ++) {
			auto x = f[i - 1][j], y = f[i - 1][j + (1 << (i - 1))];
			if (dep[x] < dep[y]) {
				f[i][j] = x;
			} else {
				f[i][j] = y;
			}
		}
	}
	auto GetLca = [&](int a, int b) {
		if (dfn[a] > dfn[b]) {
			swap(a, b);
		}
		int l = dfn[a], r = dfn[b];
		int s = __lg(r - l + 1);
		int x = f[s][l], y = f[s][r - (1 << s) + 1];
		if (dep[x] < dep[y]) {
			return x;
		} else {
			return y;
		}
	};

	for (int i = 0; i < q; i ++) {
		int u, v;
		cin >> u >> v;
		cout << GetLca(u, v) << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}