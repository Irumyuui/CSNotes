#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template <class T> constexpr T inf = std::numeric_limits<T>::max();
const int N = 2e6 + 10, M = 1e7 + 10;
struct Edge {
	int to, next;
	ll cap;
} edge[M];
int head[N], cur[N], lv[N], tt = -1;
void add(int from, int to, ll cap) {
	edge[++ tt].to = to; edge[tt].cap = cap; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].cap = cap; edge[tt].next = head[to]; head[to] = tt;
}
bool bfs(int S, int T) {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(S);
	lv[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to; ll cap = edge[ed].cap;
			if (cap > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[T] != -1;
}
ll dfs(int from, ll flow, int T) {
	if (from == T) {
		return flow;
	}
	ll lesf = flow;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to; ll cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, cap), T);
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	return flow - lesf;
}
ll dinic(int S, int T) {
	ll flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf<ll>, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	auto id = [&](int i, int j) {
		return (i - 1) * m + j;
	};
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			ll cap;
			cin >> cap;
			add(id(i, j), id(i, j + 1), cap);		
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			ll cap;
			cin >> cap;
			add(id(i, j), id(i + 1, j), cap);
		}
	}
	for (int i = 1; i < n; ++ i) {
		for (int j = 1; j < m; ++ j) {
			ll cap;
			cin >> cap;
			add(id(i, j), id(i + 1, j + 1), cap);
		}
	}
	cout << dinic(id(1, 1),id(n, m));
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}