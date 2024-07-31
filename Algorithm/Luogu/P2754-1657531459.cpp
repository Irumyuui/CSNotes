#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
#include <limits>

using namespace std;

// Disjoint Set Union
class DSU {
private:
	std::vector<int> dsu;
	int cnt;
public:
	DSU(int size = 0) : dsu(size, -1), cnt(size) {}
	void Init(int size) {
		cnt = size;
		dsu.assign(size, -1);
	}
	int& operator [] (const int id) {
		return dsu[id];
	}
	int Find(int id) {
		if (dsu[id] >= 0) {
			return dsu[id] = Find(dsu[id]);
		}
		return id;
	}
	bool Union(int a, int b) {
		a = Find(a); b = Find(b);
		if (a == b) return false;
		dsu[a] += dsu[b];
		dsu[b] = a;
		cnt --;
		return true;
	}
	bool IsSame(int a, int b) {
		return Find(a) == Find(b);
	}
	const int Count() const {
		return cnt;
	}
};

constexpr int inf = numeric_limits<int>::max();
constexpr int N = 114514, M = 1919810;

struct Edge {
	int to, cap, next;
} edge[M];
int head[N], cur[N], lv[N], tt = -1;

struct Info {
	int sum, cnt;
	vector<int> site;
};

void add(int from, int to, int cap) {
	edge[++ tt].to = to; edge[tt].cap = cap; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].cap = 0; edge[tt].next = head[to]; head[to] = tt;
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
			int to = edge[ed].to, cap = edge[ed].cap;
			if (cap > 0 && lv[to] == -1) {
				lv[to] = lv[from] + 1;
				q.push(to);
			}
		}
	}
	return lv[T] != -1;
}
int dfs(int from, int flow, int T) {
	if (from == T) {
		return flow;
	}
	int lesf = flow;
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next, cur[from] = ed) {
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, cap), T);
			if (ret > 0) {
				lesf -= ret;
				edge[ed].cap -= ret;
				edge[ed ^ 1].cap += ret;
			}
		}
	}
	return flow - lesf;
}
int dinic(int S, int T) {
	int flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m, k;
	cin >> n >> m >> k;
	int S = N - 2, T = N - 1;
	vector<Info> ship(m);	
	for (int i = 0; i < m; ++ i) {
		cin >> ship[i].sum >> ship[i].cnt;
		ship[i].site.resize(ship[i].cnt);
		for (int j = 0; j < ship[i].cnt; ++ j) {
			cin >> ship[i].site[j];
			if (ship[i].site[j] == -1) {
				ship[i].site[j] = n + 2;
			} else {
				ship[i].site[j] ++;
			}
		}
	}
	DSU dsu(n + 3);
	for (const auto &s : ship) {
		const auto &site = s.site;
		const auto &cnt = s.cnt;
		for (int i = 0; i < cnt - 1; ++ i) {
			dsu.Union(site[i], site[i + 1]);
		}
	}
	if (!dsu.IsSame(1, n + 2)) {
		cout  << 0;
		return;
	}
	int day = 0, ret = 0;
	add(S, 1, k);
	add(n + 2, T, inf);
	while (ret < k) {
		day ++;
		for (int i = 1; i < n + 2; ++ i) {
			add((day - 1) * (n + 2) + i, day * (n + 2) + i, inf);
		}
		add((n + 2) * day + n + 2, T, inf);
		for (const auto &s : ship) {
			const auto &[sum, cnt, site] = s;
			add(site[(day - 1) % cnt] + (day - 1) * (n + 2), site[day % cnt] + day * (n + 2), sum);
		}
		ret += dinic(S, T);
	}
	cout << day;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}