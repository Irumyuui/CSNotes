#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N = 2e4 + 10;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int n, m;
int dfn[N], low[N], step;
bool mk[N];
void tarjan(int u, int root) {
	dfn[u] = low[u] = ++ step;
	int cnt = 0;
	for (auto v : edge[u]) {
		if (!dfn[v]) {
			tarjan(v, root);
			low[u] = min(low[u], low[v]);
			if (low[v] >= dfn[u]) {
				cnt ++;
				if (u != root || cnt >= 2) {
					mk[u] = true;
				}
			}
		} else {
			low[u] = min(low[u], dfn[v]);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i, i);
		}
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		if (mk[i]) {
			cnt ++;
		}
	}
	cout << cnt << endl;
	for (int i = 1; i <= n; ++ i) {
		if (mk[i]) {
			cout << i << ' ';
		}
	}
}