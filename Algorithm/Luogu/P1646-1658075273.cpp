#include <bits/stdc++.h>
using namespace std;

template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
const int N = 3e5 + 10, M = 1e6 + 10;
struct Edge {
	int to, cap, next;
} edge[M];
int head[N], cur[N], lv[N], tt = -1;
void add(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
}
bool bfs(int S, int T) {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(S);
	lv[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to, cap = edge[ed].cap;
			if (cap > 0 and lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[T] != -1;
}
int dfs(int from, int flow, int T) {
	if (from == T) {
		return flow;
	}	
	int lesf = flow;
	for (int ed = cur[from]; ~ed and lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, cap), T);
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	return flow - lesf;
}
int dinic(int S, int T) {
	int flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf<int>, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	int S = N - 2, T = S + 1;
	int sum = 0;
	auto id = [&](int i, int j) {
		return (i - 1) * m + j;
	};
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int cap;
			cin >> cap;
			add(S, id(i, j), cap);
			sum += cap;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int cap;
			cin >> cap;
			add(id(i, j), T, cap);
			sum += cap;
		}
	}
	int tot = n * m;
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int cap;
			cin >> cap;
			add(S, ++ tot, cap);
			add(tot, id(i, j), inf<int>);
			add(tot, id(i + 1, j), inf<int>);
			sum += cap;
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			int cap;
			cin >> cap;
			add(++ tot, T, cap);
			add(id(i, j), tot, inf<int>);
			add(id(i + 1, j), tot, inf<int>);
			sum += cap;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			int cap;
			cin >> cap;
			add(S, ++ tot, cap);
			add(tot, id(i, j), inf<int>);
			add(tot, id(i, j + 1), inf<int>);
			sum += cap;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			int cap;
			cin >> cap;
			add(++ tot, T, cap);
			add(id(i, j), tot, inf<int>);
			add(id(i, j + 1), tot, inf<int>);
			sum += cap;
		}
	}
	cout << sum - dinic(S, T);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}