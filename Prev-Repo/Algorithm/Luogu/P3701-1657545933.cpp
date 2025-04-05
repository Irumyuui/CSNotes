#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9, N = 114514, M = 1919810;
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
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, cap), T);
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

map<string, int> td = {
	{"J", 1},
	{"E", 2},
	{"YYY", 3},
	{"HK", 4},
	{"W", 5},
};

map<int, set<int>> win = {
	// {1, 4},
	// {4, 2}
	{1, {4, 5}},
	{2, {1, 3}},
	{3, {1, 4}},
	{4, {2, 5}},
	{5, {2, 3}},
};

void Solution() {	
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	int S = n * 2 + 1, T = S + 1;
	vector<array<int,2>> a(n + 1), b(a);
	for (int i = 1; i <= n; ++ i) {
		string s;
		cin >> s;
		a[i][0] = td[s];
	}
	for (int i = 1; i <= n; ++ i) {
		string s;
		cin >> s;
		b[i][0] = td[s];
	}
	int cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i][1];
		if (a[i][0] == 3) {
			cnt ++;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		if (a[i][0] == 1) {
			a[i][1] += cnt;
		}
		add(S, i, a[i][1]);
	}
	cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		cin >> b[i][1];
		if (b[i][0] == 3) {
			cnt ++;
		}
	}
	for (int i = 1; i <= n; ++ i) {
		if (b[i][0] == 1) {
			b[i][1] += cnt;
		}
		add(i + n, T, b[i][1]);
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			if (win[a[i][0]].count(b[j][0])) {
				add(i, j + n, 1);
			}
		}
	}
	int s = T + 1, t = s + 1;
	add(s, S, m);
	add(T, t, m);
	cout << dinic(s, t);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}