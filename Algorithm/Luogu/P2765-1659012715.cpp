/* Filename: P2765 魔术球问题 */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 1e5 + 10, M = 1e6 + 10;

struct Edge {
	int to, cap, next;
	void init(auto _to, auto _cap, auto _next) {
		to = _to; cap = _cap; next = _next;
	}
} edge[M];
int head[N], cur[N], lv[N], tt = -1;

void init() {
	memset(head, -1, sizeof head);
	tt = -1;
}

void add(auto from, auto to, auto cap) {
	edge[++ tt].init(to, cap, head[from]); head[from] = tt;
	edge[++ tt].init(from, 0, head[to]); head[to] = tt;
}

auto dinic(int S, int T) {
	function<bool()> bfs = [&]() -> bool {
		memset(lv, -1, sizeof lv);
		copy(begin(head), end(head), cur);
		queue<int> q;
		q.push(S);
		lv[S] = 0;
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			for (int ed = head[from]; ~ed; ed = edge[ed].next) {
				int to = edge[ed].to, cap = edge[ed].cap;
				if (cap > 0 && lv[to] == -1) {
					lv[to] = lv[from] + 1;
					q.push(to);
				}
			}
		}
		return lv[T] != -1;
	};

	function<int(int,int)> dfs = [&](int from, int flow) {
		if (from == T) {
			return flow;
		}
		int lesf = flow;
		for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
			cur[from] = ed;
			int to = edge[ed].to, cap = edge[ed].cap;
			if (cap > 0 && lv[to] == lv[from] + 1) {
				int ret = dfs(to, min(cap, lesf));
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
		return flow - lesf;
	};

	int flow = 0;
	while (bfs()) {
		flow += dfs(S, inf<int>);
	}
	return flow;
}

void Solution() {
	init();
	int mv = 2e3 + 10;
	int n;
	cin >> n;
	int S = N - 2, T = N - 1;
	int last = 0;
	int tmp = 0;
	for (int i = 1; ; ++ i) {
		add(S, i, 1);
		add(i + mv, T, 1);
		for (int j = 1; j < i; ++ j) {
			int k = int(sqrt(i + j));
			if (k * k == i + j) {
				add(i, j + mv, 1);
			}
		}
		tmp += dinic(S, T);
		if (i - tmp > n) {
			break;
		}
		last = i;
	}
	
	debug(last);
	
	cout << last << '\n';
	vector<int> match(last + 1), sta(last + 1, true);
	for (int i = 0; i <= tt; i += 2) {
		int from = edge[i ^ 1].to, to = edge[i].to, cap = edge[i].cap;
		if (from != S && to != T && cap == 0) {
			match[to - mv] = from;
			sta[from] = false;
		}
	}

	debug(match, sta);

	function<void(int)> dfs = [&](int from) {
		if (from != 0) {
			dfs(match[from]);
			cout << from << ' ';
		}
	};
	for (int i = 1; i <= last; ++ i) {
		if (sta[i]) {
			dfs(i);
			cout << '\n';
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}