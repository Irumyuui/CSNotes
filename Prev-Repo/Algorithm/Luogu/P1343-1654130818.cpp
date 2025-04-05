#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 30;
const int N = 4e4 + 10;
struct Edge {
	int to, next = -1, w;
} edge[N];
int head[N], tt = -1;
void add(int from, int to, int w) {
	edge[++ tt].to = to; edge[tt].w = w; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].w = 0; edge[tt].next = head[to]; head[to] = tt;
}
int lv[N], cur[N];
int n, m, x, s, t;
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
	cin >> n >> m >> x;
	for (int i = 1; i <= m; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		add(from, to, w);
	}
	s = 1; t = n;
	int ans = dinic();
	if (ans == 0) {
		cout << "Orz Ni Jinan Saint Cow!";
	} else {
		cout << ans << ' ' << int(ceil(x * 1.0 / ans));
	}
}