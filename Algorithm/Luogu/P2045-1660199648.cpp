/* P2045 方格取数加强版 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES cout << "YES\n"
#define NO cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 5e5 + 10, M = 2e6 + 10;

struct Edge {
	int to, cap, cost, next;
} edge[M];
int head[N], cur[N], dis[N], tt = -1;
bool vis[N];
void add_edge(int from, int to, int cap, int cost) {
	edge[++ tt] = {to, cap, cost, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, -cost, head[to]}; head[to] = tt;
}
bool spfa(int S, int T) {
	fill(begin(dis), end(dis), inf<int>);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(S);
	dis[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		vis[from] = false;
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			auto [to, cap, cost] = array{edge[ed].to, edge[ed].cap, edge[ed].cost};
			if (cap > 0 && dis[to] > dis[from] + cost) {
				dis[to] = dis[from] + cost;
				if (!vis[to]) {
					vis[to] = true;
					q.push(to);
				}
			}
		}
	}
	return dis[T] != inf<int>;
}
int dfs(int from, int flow, int T) {
	if (from == T) return flow;
	int lesf = flow;
	vis[from] = true;
	for (int ed = cur[from]; ~ed && lesf;  ed = edge[ed].next) {
		cur[from] = ed;
		auto [to, cap, cost] = array{edge[ed].to, edge[ed].cap, edge[ed].cost};
		if (cap > 0 && !vis[to] && dis[to] == dis[from] + cost) {
			int ret = dfs(to, min(cap, lesf), T);
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	vis[from] = false;
	return flow - lesf;
}
pair<int,int> dinic(int S, int T) {
	int flow = 0, lesf = 0;
	while (spfa(S, T)) {
		int ret = dfs(S, inf<int>, T);
		flow += ret;
		lesf += ret * dis[T];
	}
	return {flow, lesf};
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, k;
	cin >> n >> k;
	vector a(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) {
		cin >> a[i][j];
	}	

	auto id = [&](int i, int j) {
		return (i - 1) * n + j;
	};
	auto check = [&](int i, int j) {
		return i >= 1 && i <= n && j >= 1 && j <= n;
	};

	int S = N - 2, T = S + 1;
	add_edge(S, id(1, 1), k, 0);
	add_edge(id(n, n) + n * n, T, k, 0);
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) {
		add_edge(id(i, j), id(i, j) + n * n, 1, -a[i][j]);
		add_edge(id(i, j), id(i, j) + n * n, inf<int>, 0);
		if (check(i + 1, j)) {
			add_edge(id(i, j) + n * n, id(i + 1, j), inf<int>, 0);
		}
		if (check(i, j + 1)) {
			add_edge(id(i, j) + n * n, id(i, j + 1), inf<int>, 0);
		}
	}
	cout << -dinic(S, T).second << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}