#include <bits/stdc++.h>
using namespace std;

const int inf = std::numeric_limits<int>::max();
const int N = 1e3 + 10;
struct Edge {
	int to, w, next;	
} edge[N * 100];
int head[N], tt = 1;
void add(int from, int to, int w) {
	edge[++ tt] = {to, w, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
}
int cur[N], lv[N], s, t, n, m;
bool bfs() {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	lv[s] = 0;
	q.push(s);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ed; ed = edge[ed].next) {
			int to = edge[ed].to, w = edge[ed].w;
			if (w > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[t] != -1;
}
int pre[N], nex[N];
bool vis[N];
int dfs(int from, int flow) {
	if (from == t) {
		return flow;
	}
	int lesf = flow;
	for (int ed = cur[from]; ed && lesf; ed = edge[ed].next) {
		cur[from] = ed; 
		int to = edge[ed].to, w = edge[ed].w;
		if (w > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(w, lesf));
			lesf -= ret;
			edge[ed].w -= ret;
			edge[ed ^ 1].w += ret;
			if (ret > 0 && from != s && to != t) {
				nex[from] = to - n;
				pre[to - n] = from;
			}
		}
	}
	return flow - lesf;
}
int dinic() {
	int flow = 0;
	while (bfs()) {
		flow += dfs(s, inf);
	}
	return flow;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr);
	cin >> n >> m;
	s = 2 * n + 1;
	t = s + 1;
	for (int i = 1; i <= n; ++ i) {
		add(s, i, 1);
		add(i + n, t, 1);
	}
	for (int i = 1; i <= m; ++ i) {
		int from, to;
		cin >> from >> to;
		add(from, to + n, 1);
	}
	int ans = n - dinic();
	function<void(int)> print = [&](int now) -> void {
		if (now == 0) {
			return;
		}
		cout << now << ' ';
		if (nex[now] != 0) {
			print(nex[now]);
		}
	};
	for (int i = 1; i <= n; ++ i) {
		if (pre[i] == 0 && !vis[i]) {
			print(i);
			cout << '\n';
		}
	}
	cout << ans << '\n';
}