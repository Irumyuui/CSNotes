#include <bits/stdc++.h>

const int N = 5e5 + 10;
std::vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].emplace_back(to);
	edge[to].emplace_back(from);
}

int dfn[N], low[N], stamp = 0;
bool iscut[N];
std::vector<std::vector<int>> bcc;
std::stack<int> st;

void dfs(int from, bool isroot) {
	dfn[from] = low[from] = ++ stamp;
	st.push(from);
	int cl_cnt = 0;
	if (edge[from].empty() && isroot) {
		bcc.push_back({from});
		return;
	}
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			dfs(to, false);
			low[from] = std::min(low[from], low[to]);
			if (low[to] >= dfn[from]) {
				cl_cnt ++;
				if (!isroot || cl_cnt >= 2) {
					iscut[from] = true;
				}
				int now = 0;
				bcc.push_back({});
				do {
					now = st.top();
					st.pop();
					bcc.back().push_back(now);
				} while (now != to);
				bcc.back().push_back(from);
			}
		} else {
			low[from] = std::min(low[from], dfn[to]);
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
		if (a == b) {
			continue;
		}
		add_edge(a, b);
	}
	for (int i = 1; i <= n; i ++) {
		if (!dfn[i]) {
			dfs(i, true);
		}
	}
	std::cout << bcc.size() << '\n';
	for (auto &i : bcc) {
		std::cout << i.size() << ' ';
		for (auto j : i) {
			std::cout << j << ' ';
		}
		std::cout << '\n';
	}
}