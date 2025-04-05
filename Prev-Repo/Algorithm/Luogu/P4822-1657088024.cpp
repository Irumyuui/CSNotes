#include <bits/stdc++.h>
using namespace std;

const int inf = std::numeric_limits<int>::max();
const int N = 2e5 + 10;
struct Edge {
	int to, w, next;
} edge[N];
int head[N], tt = 1;
void add(int from, int to, int w) {
	edge[++ tt] = {to, w, head[from]}; head[from] = tt;
}
int n, m, k;
int dis[N];
bool vis[N];
void dijkstra(int sta) {
	fill(begin(dis), end(dis), inf);
	fill(begin(vis), end(vis), false);
	priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> q;
	q.push({dis[sta] = 0, sta});
	while (!q.empty()) {
		int from = q.top().second;
		q.pop();
		if (vis[from]) {
			continue;
		}
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
	for (int _ = 0; _ < m; ++ _) {
		int from, to, tim; 
		cin >> from >> to >> tim;
		for (int i = 0; i <= k; ++ i) {
			add(from + i * n, to + i * n, tim);
			add(to + i * n, from + i * n, tim);
			if (i < k) {
				add(from + i * n, to + (i + 1) * n, tim / 2);
				add(to + i * n, from + (i + 1) * n, tim / 2);
			}
		}
	}
	dijkstra(1);
	int ans = inf;
	for (int i = 0; i <= k + 1; ++ i) {
		ans = min(ans, dis[i * n]);
	}
	cout << ans << '\n';
}