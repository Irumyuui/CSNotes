#include <iostream>
#include <cstring>
#include <limits>
#include <queue>
#include <algorithm>

using namespace std;

const int N = 3e3 + 5, M = 2e5 + 5, inf = 1 << 29;
struct Edge {
	int to, cap, next;
} edge[M];
int head[N], cur[N], lv[N], tt = -1, dcap[N];
void add(int from, int to, int low, int limit) {
	edge[++ tt] = {to, limit - low, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
}
bool bfs(int s, int t) {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(s);
	lv[s] = 0;
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
	return lv[t] != -1;
}
int dfs(int from, int flow, int t) {
	if (from == t) {
		return flow;
	}
	int lesf = flow;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(cap, lesf), t);
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	return flow - lesf;
}
int dinic(int s, int t) {
	int flow = 0;
	while (bfs(s, t)) {
		flow += dfs(s, inf, t);
	}
	return flow;
}

// day [m, n + m - 1], bba [0, m - 1]
void Solution(int n, int m) {
	memset(head, -1, sizeof head);
	tt = -1;
	int s = n + m, t = s + 1, S = t + 1, T = S + 1;
	vector<int> dcap(t + 1);
	for (int i = 0; i < m; ++ i) {
		int g;
		cin >> g;
		add(i, t, g, inf);
		dcap[i] -= g;
		dcap[t] += g;
	}
	for (int i = m; i < n + m; ++ i) {
		int c, d;
		cin >> c >> d;
		add(s, i, 0, d);
		for (int j = 0; j < c; ++ j) {
			int a, l, r;
			cin >> a >> l >> r;
			add(i, a, l, r);
			dcap[i] -= l;
			dcap[a] += l;
		}
	}
	int sum = 0;
	for (int i = 0; i <= t; ++ i) {
		if (dcap[i] > 0) {
			add(S, i, 0, dcap[i]);
			sum += dcap[i];
		} else if (dcap[i] < 0) {
			add(i, T, 0, -dcap[i]);
		}
	}
	add(t, s, 0, inf);
	if (sum != dinic(S, T)) {
		cout << -1 << '\n';
	} else {
		int ret = edge[tt].cap;
		edge[tt].cap = edge[tt - 1].cap = 0;
		ret += dinic(s, t);
		cout << ret << '\n';
	}
	cout << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	while (cin >> n >> m) {
		Solution(n, m);
	}
}