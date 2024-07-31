/* P3967 [TJOI2014]匹配 */
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

const int N = 2e3 + 10, M = 2e5 + 10;

struct Edge {
	int to, cap, cost, next;
} edge[M], medge[M], retedge[M];
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
	dis[S] = 0;
	q.push(S);
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
	if (from == T) {
		return flow;
	}
	int lesf = flow;
	vis[from] = true;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
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
	int flow = 0, cost = 0;
	while (spfa(S, T)) {
		int ret = dfs(S, inf<int>, T);
		flow += ret;
		cost += dis[T] * ret;
	}
	return {flow, cost};
}

void Solution() {
	memset(head, -1, sizeof head);
	int n;
	cin >> n;
	int S = n * 2 + 1, T = S + 1;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			int x;
			cin >> x;
			add_edge(i, j + n, 1, -x);
		}
		add_edge(S, i, 1, 0);
		add_edge(i + n, T, 1, 0);
	}
	copy(begin(edge), end(edge), medge);
	int ret = 0;
	ret = -dinic(S, T).second;
	copy(begin(edge), end(edge), retedge);
	cout << ret << '\n';
	vector<pair<int,int>> ans;
	for (int i = 0; i <= tt; i += 2) {
		int from = retedge[i ^ 1].to, to = retedge[i].to;
		if (retedge[i].cap == 0 && from >= 1 && from <= n && to >= n + 1 && to <= n + n) {
			copy(begin(medge), end(medge), edge);
			edge[i].cap = edge[i ^ 1].cap = 0;
			edge[i].cost = edge[i ^ 1].cost = 0;
			int tmp = -dinic(S, T).second;
			if (tmp < ret) {
				ans.push_back({from, to - n});
			}
		}
	}
	sort(begin(ans), end(ans));
	for (auto [a, b] : ans) {
		cout << a << ' ' << b << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}