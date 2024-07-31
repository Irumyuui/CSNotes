#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 2e3 + 10;
struct Edge {
	int to, cap, next;
	Edge(int to = {}, int cap = {}, int next = -1) : to{to}, cap{cap}, next{next} {}
} edge[N * 100];
int head[N], cur[N], lv[N];
int tt = -1;

void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}
void add_edge(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;	
}

int max_flow(int s, int t) {
	auto bfs = [&] {
		memset(lv, -1, sizeof lv);
		copy(begin(head), end(head), cur);
		lv[s] = 0;
		queue<int> q;
		q.emplace(s);
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				auto [to, cap, _] = edge[ed];
				if (cap > 0 && lv[to] == -1) {
					lv[to] = lv[from] + 1;
					q.emplace(to);
				}
			}
		}
		return lv[t] != -1;
	};
	auto dfs = [&](auto &&dfs, int from, int flow) -> int {
		if (from == t) {
			return flow;
		}
		auto lesf = flow;
		for (int &ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			auto [to, cap, _] = edge[ed];
			if (cap > 0 && lv[to] == lv[from] + 1) {
				auto ret = dfs(dfs, to, min(lesf, cap));
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

void Main() {
	init();

	int n, m;
	cin >> n >> m;

	vector<pair<int,int>> eds(m);
	for (auto &[u, v] : eds) {
		cin >> u >> v;
		u ++; v ++;
	}

	int s = n * 2 + 1, t = n * 2 + 2;
	vector<bool> vis(n * 2 + 1);
	for (auto [u, v] : eds) {
		add_edge(u, v + n, 1);
		if (!vis[u]) {
			vis[u] = true;
			add_edge(s, u, 1);
		}
		if (!vis[v + n]) {
			vis[v + n] = true;
			add_edge(v + n, t, 1);
		}
	}

	cout << n - max_flow(s, t) << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}