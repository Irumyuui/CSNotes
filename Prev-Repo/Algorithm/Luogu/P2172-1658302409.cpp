#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

std::istream& operator >> (std::istream &is, __int128_t &x) {
	x = 0; std::string s; is >> s; bool flag = false;
	for (auto ch : s) if (ch == '-') flag = true; else x = x * 10 + (ch ^ 48);
	if (flag) x = -x; return is;
}
std::ostream& operator << (std::ostream &os, __int128_t x) {
	if (x == 0) return os << '0'; bool flag = false; if (x < 0) x = -x, flag = true;
	std::string s; while (x > 0) s += x % 10 + '0', x /= 10;
	if (flag) s += '-'; std::reverse(s.begin(), s.end());
	return os << s;
}

#define all(X) std::begin(X), std::end(X)
#define lowb std::lower_bound
#define uppb std::upper_bound
#define Size(x) static_cast<int32_t>(std::size(x))
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"

using uint = uint32_t;
using ll = int64_t;
using ull = uint64_t;
using ill = __int128_t;
using uill = __uint128_t;
using ld = long double;

using namespace std;

const int N = 2e5 + 10, M = 2e6 + 10;
struct Edge {
	int to, cap, next;
} edge[M];
int head[N], lv[N], cur[N], tt = -1;
void add(int from, int to, int cap) {
	edge[++ tt] = {to, cap, head[from]}; head[from] = tt;
	edge[++ tt] = {from, 0, head[to]}; head[to] = tt;
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
	for (int ed = cur[from]; ~ed && lesf; ed = edge[ed].next) {
		cur[from] = ed;
		int to = edge[ed].to, cap = edge[ed].cap;
		if (cap > 0 && lv[to] == lv[from] + 1) {
			int ret = dfs(to, min(lesf, cap), T);
			lesf -= ret;
			edge[ed].cap -= ret;
			edge[ed ^ 1].cap += ret;
		}
	}
	return flow - lesf;
}
int dinic(int S, int T) {
	int flow = 0;
	while (bfs(S, T)) {
		flow += dfs(S, inf<int>, T);
	}
	return flow;
}

void Solution() {
	memset(head, -1, sizeof head);
	int n, m, r, c;
	cin >> n >> m >> r >> c;
	vector<pair<int,int>> D {
		{r, c}, {r, -c}, {c, r}, {c, -r},
	};
	auto id = [&](int i, int j, int k) {
		return (i - 1) * m + j + (k - 1) * n * m;
	};
	vector<vector<bool>> pos(n + 1, vector<bool>(m + 1));
	int cnt = 0;
	for (int i = 1; i <= n; ++ i) {
		string s;
		cin >> s;
		for (int j = 1; j <= m; ++ j) {
			int x = s[j - 1] == '.';
			pos[i][j] = x;
			cnt += x;
		}
	}
	auto check = [&](int i, int j) -> bool {
		if (i >= 1 && i <= n && j >= 1 && j <= m) {
			return pos[i][j];
		}
		return false;
	};
	int S = N - 2, T = S + 1;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			if (pos[i][j]) {
				add(S, id(i, j, 1), 1);
				add(id(i, j, 2), T, 1);
				for (auto [di, dj] : D) {
					int ni = i + di, nj = j + dj;
					if (check(ni, nj)) {
						add(id(i, j, 1), id(ni, nj, 2), 1);
					}
				}
			}
		}
	}
	cout << cnt - dinic(S, T);
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}