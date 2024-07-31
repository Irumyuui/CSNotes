#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll inf = 1ll << 60;
const int N = 1e4 + 10;
struct Edge {
	int to, next;
	ll w;
};
Edge edge[N];
int head[N], tt = 1;
inline void add(int from, int to, ll w) {
	edge[++ tt].to = to; edge[tt].w = w; edge[tt].next = head[from]; head[from] = tt;
}
int n, m, s, t, lv[N], cur[N];
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
			int to = edge[ed].to;
			ll w = edge[ed].w;
			if (w > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[t] != -1;
}
ll dfs(int from, ll flow) {
	if (from == t) {
		return flow;
	}
	ll lesf = flow;
	for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to;
		ll w = edge[ed].w;
		if (w > 0 && lv[to] == lv[from] + 1) {
			ll ret = dfs(to, min(w, lesf));
			lesf -= ret;
			edge[ed].w -= ret;
			edge[ed ^ 1].w += ret;
		}
	}
	return flow - lesf;
}
ll dinic() {
	ll ans = 0;
	while (bfs()) {
		ans += dfs(s, inf);
	}
	return ans;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(head, -1, sizeof head);
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= m; ++ i) {
		int from, to; ll w;
		cin >> from >> to >> w;
		add(from, to, w);
		add(to, from, 0);
	}
	cout << dinic();
}