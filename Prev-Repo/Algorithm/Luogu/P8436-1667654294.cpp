#include <bits/stdc++.h>

const int N = 5e5 + 10, M = 2e6 + 10;
std::vector<std::pair<int,int>> edge[N];
void add_edge(int from, int to, int id) {
	edge[from].emplace_back(to, id);
	edge[to].emplace_back(from, id);
}

int dfn[N], low[N], stamp = 0;
bool bridge[M];

void dfs(int from, int id) {
	dfn[from] = low[from] = ++ stamp;
	for (auto [to, eid] : edge[from]) {
		if (!dfn[to]) {
			dfs(to, eid);
			low[from] = std::min(low[from], low[to]);
		} else if (id != eid) {
			low[from] = std::min(low[from], dfn[to]);
		}
	}
	if (dfn[from] == low[from] && id != -1) {
		bridge[id] = true;
	}
}

std::vector<std::vector<int>> dcc;
bool vis[N];
void dfs(int from) {
	vis[from] = true;
	dcc.back().push_back(from);
	for (auto [to, id] : edge[from]) {
		if (!bridge[id] && !vis[to]) {
			dfs(to);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	for (int i = 1; i <= m; i ++) {
		int a, b;
		std::cin >> a >> b;
		add_edge(a, b, i);
	}
	for (int i = 1; i <= n; i ++) {
		if (!dfn[i]) {
			dfs(i, -1);
		}
	}
	for (int i = 1; i <= n; i ++) {
		if (!vis[i]) {
			dcc.push_back({});
			dfs(i);
		}
	}
	std::cout << dcc.size() << '\n';
	for (const auto &i : dcc) {
		std::cout << i.size() << ' ';
		for (auto j : i) {
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
}