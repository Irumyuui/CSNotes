/* P1559 运动员最佳匹配问题 */
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

const int N = 114514, M = 1919810;
struct Edge {
	int to, cap, cost, next;
} edge[M];
int head[N], cur[N], dis[N], tt = -1;
bool vis[N];

void add_edge(int from, int to, int cap, int cost) {
	edge[++ tt] = {to, cap, cost, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, -cost, head[to]}; head[to] = tt;
}

void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}

pair<int,int> dinic(int S, int T) {
	function<bool()> spfa = [&]() {
		fill(begin(dis), end(dis), inf<int>);
		copy(begin(head), end(head), cur);
		dis[S] = 0;
		queue<int> q;
		q.push(S);
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			vis[from] = false;

			debug(from);

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
	};
	function<int(int,int)> dfs = [&](int from, int flow) {
		debug(from, flow);
		if (from == T) {
			return flow;
		}
		int lesf = flow;
		vis[from] = true;
		for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			cur[from] = ed;
			auto [to, cap, cost] = array{edge[ed].to, edge[ed].cap, edge[ed].cost};
			if (cap > 0 && !vis[to] && dis[to] == dis[from] + cost) {
				int ret = dfs(to, min(lesf, cap));
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
		vis[from] = false;
		return flow - lesf;
	};
	int flow = 0, cost = 0;
	while (spfa()) {
		int ret = dfs(S, inf<int>);
		flow += ret;
		cost += dis[T] * ret;
		debug(flow, cost);
	}
	return {flow, cost};
}

void Solution() {
	init();
	int n;
	cin >> n;
	vector a(n + 1, vector<int>(n + 1)), b(a);
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) cin >> a[i][j];
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) cin >> b[i][j];
	int S = N - 1, T = N - 2;
	for (int i = 1; i <= n; ++ i) {
		add_edge(S, i, 1, 0);
		add_edge(i + n, T, 1, 0);
	}
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) {
		add_edge(i, j + n, 1, -(a[i][j] * b[j][i]));
	}
	cout << -dinic(S, T).second << '\n';
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}