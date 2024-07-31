#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 30;
const int N = 5e5 + 10;
struct Edge {
	int to, w, next;
} edge[N];
int head[N], tt = -1, lv[N], cur[N];
void add(int from, int to, int w) {
	edge[++ tt].to = to; edge[tt].w = w; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].w = 0; edge[tt].next = head[to]; head[to] = tt;
}
int s, t;
int n, m;
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
	for (int ed = cur[from]; ed != -1  && lesf > 0; ed = edge[ed].next) {
		int to = edge[ed].to, w = edge[ed].w;
		if (w > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, w));
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
	cin >> n >> m;
	s = n + 1; t = s + 1;
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		if (x == 1) {
			add(s, i, 1);
		} else {
			add(i, t, 1);
		}
	}
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b, 1);
		add(b, a, 1);
	}
	cout << dinic();
}