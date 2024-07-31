#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

const int N = 200;
vector<int> g[N];
std::vector<int> edge[N];
void adde(int from, int to) {
	edge[from].push_back(to);
}
int n, m;
int cat[N];
bool vis[N];
bool match(int u) {
	for (auto v : edge[u]) {
		if (!vis[v]) {
			vis[v] = true;
			if (!cat[v] || match(cat[v])) {
				cat[v] = u;
				return true;
			}
		}
	}
	return false;
}

void dfs(int now) {
	cout << now << ' ';
	for (auto nex : g[now]) {
		dfs(nex);
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		int x, y;
		cin >> x >> y;
		adde(x, y);
	}
	memset(cat, 0, sizeof cat);
	int cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		memset(vis, 0, sizeof vis);
		if (match(i)) {
			cnt ++;
		}
	}
	queue<int> q;
	for (int i = 1; i <= n; ++ i) {
		if (cat[i]) {
			g[cat[i]].push_back(i);
		} else {
			q.push(i);
		}
	}
	while (!q.empty()) {
		int sta = q.front();
		q.pop();
		dfs(sta);
		cout << endl;
	}
	cout << n - cnt << endl;
}