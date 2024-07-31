#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 29;
const int N = 1e5 + 10;
int s, t, n, m;
struct Graph {
	struct Edge {
		int to, w, next;
	} edge[N];
	int tt, head[N];
	int lv[N], cur[N];
	Graph() {
		memset(head, -1, sizeof head);
		tt = 1;
	}
	void add(int from, int to, int w) {
		edge[++ tt].to = to; edge[tt].w = w; edge[tt].next = head[from]; head[from] = tt;
		edge[++ tt].to = from; edge[tt].w = 0; edge[tt].next = head[to]; head[to] = tt;
	}
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
} e, g;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	s = 1; t = n;
	for (int i = 1; i <= m; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		g.add(from, to, w);
		e.add(from, to, 1);
	}
	cout << g.dinic() << ' ' << e.dinic();
}