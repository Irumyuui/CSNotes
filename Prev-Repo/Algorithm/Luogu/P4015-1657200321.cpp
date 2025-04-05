#include <bits/stdc++.h>
using namespace std;

const int inf = numeric_limits<int>::max();
const int N = 510, M = 1e6 + 10;
struct Edge {
	int to, w, cost, next;
} edge[M];
int head[N], tt = 1;
void add(int from, int to, int w, int cost) {
	edge[++ tt] = {to, w, cost, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, -cost, head[to]}; head[to] = tt;
}
int cur[N], dis[N];
bool vis[N];
int s, t, n, m;
int a[N], b[N], c[N][N];
int dfs(int from, int flow) {
	if (from == t) {
		return flow;
	}
	int lesf = flow;
	vis[from] = true;
	for (int ed = cur[from]; ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, w = edge[ed].w, cost = edge[ed].cost;
		if (w > 0 && !vis[to] && dis[to] == dis[from] + cost) {
			int ret = dfs(to, min(lesf, w));
			lesf -= ret;
			edge[ed].w -= ret;
			edge[ed ^ 1].w += ret;
		}
	}
	vis[from] = false;
	return flow - lesf;
}
int dinic() {
	function<bool()> spfa = [&]() {
		fill(begin(dis), end(dis), inf);
		copy(begin(head), end(head), cur);
		queue<int> q;
		q.push(s);
		dis[s] = 0;
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			vis[from] = false;
			for (int ed = head[from]; ed; ed = edge[ed].next) {
				int to = edge[ed].to, w = edge[ed].w, cost = edge[ed].cost;
				if (w > 0 && dis[to] > dis[from] + cost) {
					dis[to] = dis[from] + cost;
					if (!vis[to]) {
						q.push(to);
						vis[to] = true;
					}
				}
			}
		}
		return dis[t] != inf;
	};
	int cost = 0;
	while (spfa()) {
		int ret = dfs(s, inf);
		cost += ret * dis[t];
	}
	return cost;
}
auto Solution() {
	cin >> n >> m;
	s = n + m + 1;
	t = s + 1;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	for (int i = 1; i <= m; ++ i) {
		cin >> b[i];
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cin >> c[i][j];
		}
	}
	function<void(int)> build = [&](int inv) -> void {
		memset(head, 0, sizeof head);
		tt = 1;
		for (int i = 1; i <= n; ++ i) {
			add(s, i, a[i], 0);
		}
		for (int i = 1; i <= m; ++ i) {
			add(i + n, t, b[i], 0);
		}
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= m; ++ j) {
				add(i, j + n, b[j], c[i][j] * inv);
			}
		}
	};
	build(1);
	cout << dinic() << '\n';
	build(-1);
	cout << -dinic() << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}