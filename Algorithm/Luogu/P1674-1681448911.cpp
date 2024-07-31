#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

using i64 = int64_t;

const int N = 210;
struct Edge {
	int to, cap, next;
} edge[int(1e5 + 10)];
int head[N], cur[N], lv[N], tt = -1;
void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}
void add_edge(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, cap, head[to]}; head[to] = tt;
}

int max_flow(int s, int t) {
	auto bfs = [&]() {
		fill(begin(lv), end(lv), -1);
		copy(begin(head), end(head), begin(cur));
		queue<int> q;
		q.emplace(s);
		lv[s] = 0;
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				int to = edge[ed].to, cap = edge[ed].cap;
				if (cap > 0 && lv[to] == -1) {
					lv[to] = lv[from] + 1;
					q.emplace(to);
				}
			}
		}
		return lv[t] != -1;
	};
	auto dfs = [&](auto &&dfs, int from, int flow) {
		if (from == t) 
			return flow;
		int lesf = flow;
		for (int &ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			int to = edge[ed].to, cap = edge[ed].cap;
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
	int n, m, t;
	cin >> n >> m >> t;
	vector<tuple<int,int,i64>> eds(m);
	for (auto &[u, v, w] : eds) {
		cin >> u >> v >> w;
	}

	auto check = [&](i64 limit) {
		init();
		for (auto [u, v, w] : eds) {
			if (w <= limit) {
				add_edge(u, v, 1);
			}
		}
		return max_flow(1, n) >= t;
	};

	i64 l = 0, r = inf<i64>, ans = -1;
	while (l <= r) {
		i64 mid = l + ((r - l) >> 1);
		if (check(mid)) {
			ans = mid;
			r = mid - 1;
		} else {
			l = mid + 1;
		}
	}
	assert(ans > -1);
	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}