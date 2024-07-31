#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 30, N = 514, M = 114514;
struct Edge {
	int to, cap, cost, next;
} edge[M];
int head[N], dis[N], cur[N], tt = -1;
bool vis[N];
void add(int from, int to, int cap, int cost) {
	edge[++ tt].to = to; edge[tt].cap = cap; edge[tt].cost = cost; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].cap = 0; edge[tt].cost = -cost; edge[tt].next = head[to]; head[to] = tt;
}
bool spfa(int S, int T) {
	// memset(lv, -1, sizeof lv);
	fill(begin(dis), end(dis), inf);
	copy(begin(head), end(head), cur);
	// deque<int> q;
	queue<int> q;
	q.emplace(S);
	dis[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		// q.pop_front();
		q.pop();
		vis[from] = false;
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to, cap = edge[ed].cap, cost = edge[ed].cost;
			if (cap > 0 && dis[to] > dis[from] + cost) {
				dis[to] = dis[from] + cost;
				if (!vis[to]) {
					// if (q.empty() || dis[to] < dis[q.front()]) {
					// 	q.emplace_front(to);
					// } else {
					// 	q.emplace_back(to);
					// }
					q.emplace(to);
					vis[to] = true;
				}
			}
		}
	}
	return dis[T] != inf;
}
int dfs(int from, int flow, int T) {
	if (from == T) {
		return flow;
	}
	int lesf = flow;
	vis[from] = true;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, cap = edge[ed].cap, cost = edge[ed].cost;
		if (cap > -0 && !vis[to] && dis[to] == dis[from] + cost) {
			int ret = dfs(to, min(lesf, cap), T);
			if (ret > 0) {
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
	}
	vis[from] = false;
	return flow - lesf;
}
int dinic(int S, int T) {
	int ret = 0;
	while (spfa(S, T)) {
		ret += dfs(S, inf, T) * dis[T];
	}
	return ret;
}

void Solution() {
	int n;
	cin >> n;
	int S = n * 2 + 1, T = S + 1;
	vector c(n + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			cin >> c[i][j];
		}
	}
	auto build = [&](int d) {
		memset(head, -1, sizeof head);
		tt = -1;
		for (int i = 1; i <= n; ++ i) {
			add(S, i, 1, 0);
			add(i + n, T, 1, 0);
		}
		for (int i = 1; i <= n; ++ i) {
			for (int j = 1; j <= n; ++ j) {
				add(i, j + n, 1, d * c[i][j]);
			}
		}
	};
	build(1);
	cout << dinic(S, T) << '\n';
	build(-1);
	cout << -dinic(S, T) << '\n';
	/*
	for (int i = 1; i <= n; ++ i) {
		add(S, i, 1, 0);
		add(i + n, T, inf, 0);
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			int c;
			cin >> c;
			add(i, j + n, c, 1);
		}
	}
	cout << dinic(S, T) << '\n';
	*/
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}