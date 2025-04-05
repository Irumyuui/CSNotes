#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll = long long;

const ll inf = 1ll << 60;
const int N = 1e5 + 10;
struct Edge {
	int to, next;
	ll w, cost;
} edge[N * 10];
int head[N], tt = -1;
void add(int from, int to, ll w, ll cost) {
	edge[++ tt].to = to;
	edge[tt].w = w;
	edge[tt].cost = cost;
	edge[tt].next = head[from];
	head[from] = tt;

	edge[++ tt].to = from;
	edge[tt].w = 0;
	edge[tt].cost = -cost;
	edge[tt].next = head[to];
	head[to] = tt;
}
ll dis[N];
int cur[N];
bool vis[N];
int n, m, s, t;
bool spfa() {
	copy(begin(head), end(head), cur);
	fill(begin(dis), end(dis), inf);
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		vis[from] = false;
		for (int ed = head[from]; ed != -1; ed = edge[ed].next) {
			int to = edge[ed].to;
			ll w = edge[ed].w, cost = edge[ed].cost;
			if (w > 0 && dis[to] > dis[from] + cost) {
				dis[to] = dis[from] + cost;
				if (!vis[to]) {
					q.push(to);
					vis[to] = true;
				}
			}
		}
	}
	return dis[t] != inf;
}
ll dfs(int from, ll flow) {
	if (from == t) {
		return flow;
	}
	ll lesf = flow;
	vis[from] = true;
	for (int ed = cur[from]; ed != -1 && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to;
		ll w = edge[ed].w, cost = edge[ed].cost;
		if (w > 0 && !vis[to] && dis[to] == dis[from] + cost) {
			ll ret = dfs(to, min(lesf, w));
			lesf -= ret;
			edge[ed].w -= ret;
			edge[ed ^ 1].w += ret;
		}
	}
	vis[from] = false;
	return flow - lesf;
}
pair<ll, ll> dinic() {
	ll flow = 0, cost = 0;
	while (spfa()) {
		ll ret = dfs(s, inf);
		flow += ret;
		cost += ret * dis[t]; 
	}
	return {flow, cost};
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(head, -1, sizeof head);
	cin >> n >> m >> s >> t;
	for (int i = 0; i < m; ++ i) {
		int from, to;
		ll w, cost;
		cin >> from >> to >> w >> cost;
		add(from, to, w, cost);
	}
	auto [flow, cost] = dinic();
	cout << flow << ' ' << cost << endl;
}