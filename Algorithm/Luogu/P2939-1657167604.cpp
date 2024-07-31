#include <bits/stdc++.h>
using namespace std;
const int inf = numeric_limits<int>::max();
const int N = 5e6 + 10;
struct Edge {
	int to, w, next;
} edge[N << 2];
int head[N], tt = 1;
void add(int from, int to, int w) {
	edge[++ tt] = {to, w, head[from]}; head[from] = tt;
}
int dis[N], n, m, k;
bool vis[N];
void dijkstra(int sta) {
	fill(begin(dis), end(dis), inf);
	memset(vis, 0, sizeof vis);
	priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
	q.push({dis[sta] = 0, sta});
	while (!q.empty()) {
		int from = q.top().second;
		q.pop();
		if (vis[from]) continue;
		vis[from] = true;
		for (int ed = head[from]; ed; ed = edge[ed].next) {
			int to = edge[ed].to, w = edge[ed].w;
			if (!vis[to] && dis[to] > dis[from] + w) {
				dis[to] = dis[from] + w;
				q.push({dis[to], to});
			}
		}
	}
}
int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m >> k;
	for (int i = 1; i <= m; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		for (int i = 0; i <= k; ++ i) {
			add(from + i * n, to + i * n, w);
			add(to + i * n, from + i * n, w);
			if (i < k) {
				add(from + i * n, to + (i + 1) * n, 0);
				add(to + i * n, from + (i + 1) * n, 0);
			}
		}
	}
	dijkstra(1);
	int ans = inf;
	for (int i = 0; i <= k + 1; ++ i) {
		ans = min(ans, dis[n + i * n]);
	}
	cout << ans;
}