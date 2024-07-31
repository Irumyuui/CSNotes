#include <bits/stdc++.h>
using namespace std;

const int inf = 1 << 29;
const int N = 5e6 + 10;
struct Edge {
	int to, w, next;
} edge[N];
int head[N], lv[N], cur[N], tt = 1;
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
	cin >> n;
	s = n + 1; t = s + 1;
	int v1 = t + 1, v2 = t + 2, sum = 0;
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		add(s, i, x);
		sum += x;
	}
	for (int i = 1; i <= n; ++ i) {
		int x;
		cin >> x;
		add(i, t, x);
		sum += x;
	}
	cin >> m;
	for (int i = 1; i <= m; ++ i) {
		int k, c1, c2;
		cin >> k >> c1 >> c2;
		add(s, v1, c1);
		add(v2, t, c2);
		sum += c1 + c2;
		for (int i = 1; i <= k; ++ i) {
			int x;
			cin >> x;
			add(v1, x, inf);
			add(x, v2, inf);
		}
		v1 += 2; v2 += 2;
	}
	cout << sum - dinic();
}