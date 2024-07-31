#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

constexpr int inf = 1 << 30;
constexpr int N = 1e5+ 5, M = 5e6 + 5;

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
			if (cap > 0 && lv[to] == -1) {
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
	for (int ed = cur[from]; ~ed && lesf; ed= edge[ed].next, cur[from] = ed) {
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(cap, lesf), T);
			if (ret > 0) {
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
	}
	return flow - lesf;
}

int dinic(int S, int T) {
	int flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n1, n2, n3;
	cin >> n1 >> n2 >> n3;
	int S = N - 2, T = N - 1;
	for (int i = 1; i <= n1; ++ i) {
		add(i, i + n1, 1);
	}
	for (int i = 1; i <= n2; ++ i) {
		add(S, 2 * n1 + i, 1);
	}
	for (int i = 1; i <= n3; ++ i) {
		add(2 * n1 + n2 + i, T, 1);
	}
	int m;
	cin >> m;
	while (m --) {
		int x, y;
		cin >> x >> y;
		add(2 * n1 + y, x, 1);
	}
	cin >> m;
	while (m --) {
		int x, y;
		cin >> x >> y;
		add(x + n1, y + 2 * n1 + n2, 1);
	}
	cout << dinic(S, T);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}