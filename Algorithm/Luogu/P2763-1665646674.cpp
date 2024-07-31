/* P2763 试题库问题 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
std::mt19937 mrand(std::chrono::system_clock::now().time_since_epoch().count());
using ll = int64_t;
using ld = long double;

const int N = 2e3 + 10, M = 1919810;
struct Edge {
	int to, cap, next = -1;
} edge[M];
int head[N], cur[N], lv[N], tt = -1;
void init() {
	tt = -1;
	memset(head, -1, sizeof(head));
}
void add_edge(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
}
int maxflow_dinic(int s, int t) {
	auto bfs = [&]() -> bool {
		memset(lv, -1, sizeof(lv));
		std::copy(std::begin(head), std::end(head), cur);
		lv[s] = 0;
		std::queue<int> q;
		q.push(s);
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				auto [to, cap] = std::tuple{edge[ed].to, edge[ed].cap};
				if (cap > 0 && lv[to] == -1) {
					lv[to] = lv[from] + 1;
					q.push(to);
				}
			}
		}
		return lv[t] != -1;
	};
	auto dfs = [&](auto &&dfs, int from, int flow) -> int {
		if (from == t) {
			return flow;
		}
		int lesf = flow;
		for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			cur[from] = ed;
			auto [to, cap] = std::tuple{edge[ed].to, edge[ed].cap};
			if (cap > 0 && lv[to] == lv[from] + 1) {
				int ret = dfs(dfs, to, std::min(cap, lesf));
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		} 
		return flow - lesf;
	};
	int flow = 0;
	while (bfs()) {
		flow += dfs(dfs, s, inf<int>);
	}
	return flow;
}

void Solution() {
	init();
	int k, n;
	cin >> k >> n;
	
	int m = 0;
	int S = N - 2, T = S + 1;
	for (int i = 1; i <= k; i ++) {
		int w;
		cin >> w;
		m += w;
		add_edge(i + n, T, w);
	}
	for (int i = 1; i <= n; i ++) {
		add_edge(S, i, 1);
		int p;
		cin >> p;
		while (p --) {
			int x;
			cin >> x;
			add_edge(i, x + n, 1);
		}
	}

	if (m == maxflow_dinic(S, T)) {
		vector<vector<int>> ls(k + 1);
		for (int i = 0; i <= tt; i += 2) {
			int to = edge[i].to, from = edge[i ^ 1].to, cap = edge[i].cap;
			if (cap == 0 && to >= n + 1 && to <= n + k && from >= 1 && from <= n) {
				ls[to - n].push_back(from);
			}
		}
		for (int i = 1; i <= k; i ++) {
			cout << i << ": ";
			for (auto j : ls[i]) {
				cout << j << ' ';
			}
			cout << '\n';
		}
	} else {
		cout << "No Solution!" << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}