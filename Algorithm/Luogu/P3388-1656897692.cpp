#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int dfn[N], low[N], stamp = 0;
bool yes[N];
void tarjan(int from, int root) {
	dfn[from] = low[from] = ++ stamp;
	int tree_cnt = 0;
	for (int to : edge[from]) {
		if (!dfn[to]) {
			tarjan(to, root);
			low[from] = min(low[from], low[to]);
			if (low[to] >= dfn[from]) {
				tree_cnt ++;
				if (from != root || tree_cnt >= 2) {
					yes[from] = true;
				}
			}
		} else {
			low[from] = min(low[from], dfn[to]);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int from, to;
		cin >> from >> to;
		add(from, to);
		add(to, from);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i, i);
		}
	}
	cout << count(yes + 1, yes + 1 + n, true) << '\n';
	for (int i = 1; i <= n; ++ i) {
		if (yes[i]) {
			cout << i << ' ';
		}
	}
}