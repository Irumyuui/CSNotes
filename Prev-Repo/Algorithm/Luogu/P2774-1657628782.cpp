#include <bits/stdc++.h>

// #include <debug.h>

using namespace std;
using ll = long long;

// #include <type_traits>
constexpr ll inf = std::numeric_limits<std::decay<decltype(inf)>::type>::max();
// constexpr int inf = 1 << 29;
constexpr int N = 1e5 + 10, M = 1919810;

struct Edge {
	int to, next;
	std::decay<decltype(inf)>::type cap;
	auto init(int _to, std::decay<decltype(cap)>::type _cap, int _next) -> void {
		to = _to; cap = _cap; next = _next;
	}
};

Edge edge[M];
int head[N], cur[N], lv[N], tt = -1;

auto add(int from, int to, std::decay<decltype(inf)>::type cap) -> void {
	edge[++ tt].init(to, cap, head[from]); head[from] = tt;
	edge[++ tt].init(from, 0, head[to]); head[to] = tt;
	// debug(from, to, cap);
}

auto bfs(int S, int T) -> bool {
	memset(lv, -1, sizeof lv);
	copy(begin(head), end(head), cur);
	queue<int> q;
	q.push(S);
	lv[S] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		for (int ed = head[from]; ~ed; ed = edge[ed].next) {
			int to = edge[ed].to;
			auto cap = edge[ed].cap;
			if (cap > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[T] != -1;
}

auto dfs(int from, std::decay<decltype(inf)>::type flow, int T) -> std::decay<decltype(inf)>::type {
	if (from == T) {
		return flow;
	}
	auto lesf = flow;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to;
		auto cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			auto ret = dfs(to, min(lesf, cap), T);
			if (ret > 0) {
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
	}
	return flow - lesf;
}

auto dinic(int S, int T) -> std::decay<decltype(inf)>::type {
	std::decay<decltype(inf)>::type flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m;
	cin >> n >> m;
	ll sum = 0;
	vector a(n + 1, vector(m + 1, 0ll));
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cin >> a[i][j];
			sum += a[i][j];
		}
	}
	int S = N - 1, T = N - 2;
	array<pair<int,int>, 4> D{pair{-1, 0}, pair{1, 0}, pair{0, -1}, pair{0, 1}};
	vector<vector<int>> id(102, vector<int>(102));
	{
		int tot = 0;
		for (int i = 1; i < 102; ++ i) {
			for (int j = 1; j < 102; ++ j) {
				id[i][j] = ++ tot;
			}
		} 
	}
	// debug(id);
	auto getid = [&](int i, int j) {
		return id[i][j];
	};
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			// int p = (i - 1) * m + j;
			int p = getid(i, j);
			if (p & 1) {
				add(S, p, a[i][j]);
				for (auto [dx, dy] : D) {
					int x = i + dx, y = j + dy;
					if (x > 0 && x <= n && y > 0 && y <= m) {
						int q = getid(x, y);
						add(p, q, inf);
						// if (p % 2 && !(q % 2)) {
						// 	debug(p, q);
						// }
						// cerr << p << ' ' << q << " 3\n";
					}
				}
				// cerr << 1 << ' ' << p << '\n';
			} else {
				add(p, T, a[i][j]);
				// cerr << 2 << ' ' << p << '\n';
			}
		}
	}
	cout << sum - dinic(S, T);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}