#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1 << 29;
constexpr int N = 1010, M = 1e6 + 10;
struct Edge {
	int to, w, next;
} edge[M];
int head[N], tt = -1;
int lv[N], cur[N], S, T;
int a[N], f[N];
void add(int from, int to, int w) {
	edge[++ tt] = Edge{to, w, head[from]}; head[from] = tt;
	edge[++ tt] = Edge{from, w, head[to]}; head[to] = tt;
}
bool bfs() {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(S);
	lv[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to, w = edge[ed].w;
			if (w > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[T] != -1;
}
int dfs(int from, int flow) {
	if (from == T) {
		return flow;
	}
	int lesf = flow;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, w = edge[ed].w;
		if (w > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(w, lesf));
			lesf -= ret;
			edge[ed].w -= ret;
			edge[ed ^ 1].w += ret;
		}
	}
	return flow - lesf;
}
int dinic() {
	int flow = 0;
	while (bfs()) {
		flow += dfs(S, inf);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
	}
	int mxlen = 0;
	for (int i = 1; i <= n; ++ i) {
		f[i] = 1;
		for (int j = 1; j < i; ++ j) {
			if (a[j] <= a[i]) {
				f[i] = max(f[i], f[j] + 1);
			}
		}
		mxlen = max(mxlen, f[i]);
	}
	cout << mxlen << '\n';
	if (mxlen == 1) {
		cout << n << '\n' << n << '\n';
		return;
	}
	S = n * 2 + 1, T = S + 1;
	for (int i = 1; i <= n; ++ i) {
		add(i, i + n, 1);
		if (f[i] == 1) {
			add(S, i, 1);
		}
		if (f[i] == mxlen) {
			add(n + i, T, 1);
		}
		for (int j = 1; j < i; ++ j) {
			if (a[j] <= a[i] && f[j] + 1 == f[i]) {
				add(j + n, i, 1);
			}
		}
	}
	int ans = dinic();
	cout << ans << '\n';
	for (int i = 0; i <= tt; i += 2) {
		int from = edge[i ^ 1].to, to = edge[i].to;
		if (from == S && to == 1) {
			edge[i].w = inf;
		}
		if (from == n + n && to == T) {
			edge[i].w = inf;
		}
		if (from == 1 && to == 1 + n) {
			edge[i].w = inf;
		}
		if (from == n && to == n + n) {
			edge[i].w = inf;
		}
	}
	ans += dinic();
	cout << ans;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}