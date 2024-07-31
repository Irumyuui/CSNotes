#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
vector<pair<int,int>> edge[N];
void add(int from, int to, int id) {
	edge[from].push_back({to, id});
	edge[to].push_back({from, id});
}

int dfn[N], low[N], stamp = 0;
vector<int> bridge;  // 割边
void tarjan(int from, int id) {
	dfn[from] = low[from] = ++ stamp;
	for (auto [to, _id] : edge[from]) {
		if (!dfn[to]) {
			tarjan(to, _id);
			low[from] = min(low[from], low[to]);
		} else if (id != _id) {
			low[from] = min(low[from], dfn[to]);
		}
	}
	if (dfn[from] == low[from] && id != -1) {
		bridge.push_back(id);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b, i);
	}	
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i, -1);
		}
	}
	int ans = bridge.size();
	cout << ans << '\n';
	// sort(begin(bridge), end(bridge));
	// for (auto x : bridge) {
	// 	cout << x << ' ';
	// }
}