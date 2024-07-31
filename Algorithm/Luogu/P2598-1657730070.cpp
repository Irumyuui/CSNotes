#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 29, N = 2e5 + 10, M = 2e6 + 10;
struct Edge {
	int to, cap, next;
} edge[M];
int head[N], cur[N], lv[N], tt = -1;
void add(int from, int to, int cap) {
	edge[++ tt].to = to; edge[tt].cap = cap; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].cap = 0; edge[tt].next = head[to]; head[to] = tt;
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
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
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
		flow += dfs(S, inf, T);
	}
	return flow;
}

vector<pair<int,int>> D {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1}
};

void Solution() {
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	vector a(n + 1, vector<int>(m + 1));
	// int S = N - 2, T = N - 1;
	int S = n * m + 1, T = S + 1;
	auto getid = [&](int i, int j) {
		return (i - 1) * m + j;
	};
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cin >> a[i][j];
			if (a[i][j] == 1) {
				add(S, getid(i, j), inf);
			} else if (a[i][j] == 2) {
				add(getid(i, j), T, inf);
			}
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			for (const auto &[di, dj] : D) {
				int ni = i + di, nj = j + dj;
				if (ni > 0 && ni <= n && nj > 0 && nj <= m) {
					add(getid(i, j), getid(ni, nj), 1);
				}
			}
		}
	}
	cout << dinic(S, T);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}