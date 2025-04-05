#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 10;
const int inf = 1 << 30;
struct Edge {
	int to, w, next;
} edge[N];
int head[N], tt = -1;
void add(int from, int to, int w) {
	edge[++ tt].to = to; edge[tt].w = w; edge[tt].next = head[from]; head[from] = tt; 
	edge[++ tt].to = from; edge[tt].w = 0; edge[tt].next = head[to]; head[to] = tt;
}
int lv[N], cur[N];
int s, t;
int n, f, d;
bool bfs() {
	copy(begin(head), end(head), cur);
	memset(lv, -1, sizeof lv);
	lv[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
			int to = edge[ed].to, w = edge[ed].w;
			if (w > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[t] != -1;
}
int dfs(int from, int flow) {
	if (from == t) {
		return flow;
	}
	int lesf = flow;
	for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
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
	int ans = 0;
	while (bfs()) {
		ans += dfs(s, inf);
	}
	return ans;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(head, -1, sizeof head);
	cin >> n >> f >> d;
	s = f + n + n + d + 1; t = f + n + n + d + 2;
	for (int i = 1; i <= n; ++ i) {
		add(i + f, i + f + n, 1);
	}
	for (int i = 1; i <= f; ++ i) {
		add(s, i, 1);
	}
	for (int i = 1; i <= d; ++ i) {
		add(i + f + n + n, t, 1);
	}
	for (int i = 1; i <= n; ++ i) {
		int fi, di;
		cin >> fi >> di;
		for (int j = 1; j <= fi; ++ j) {
			int x;
			cin >> x;
			add(x, i + f, 1);
		}
		for (int j = 1; j <= di; ++ j) {
			int x;
			cin >> x;
			add(i + f + n, x + f + n + n, 1);
		}
	}
	cout << dinic();
}