/* P8025 [ONTAK2015] Związek Harcerstwa Bajtockiego */
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
using ll = int64_t;
using ld = long double;

using std::swap;

const int N = 2e6 + 10;

struct Edge {
	int to, next;
} edge[N];
int head[N];
int tt = 0;

void add_edge(int from, int to) noexcept {
	edge[++ tt].to = to; edge[tt].next = head[from]; head[from] = tt;
	edge[++ tt].to = from; edge[tt].next = head[to]; head[to] = tt;
}

int son[N], fa[N], top[N], siz[N], dfn[N], dep[N], rnk[N];
int stamp = 0;

void dfs1(int from) noexcept {
	son[from] = -1;
	siz[from] = 1;
	for (int ed = head[from]; ed; ed = edge[ed].next) {
		int to = edge[ed].to;
		if (dep[to] == 0) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to);
			siz[from] += siz[to];
			if (son[from] == -1 || siz[to] > siz[son[from]]) {
				son[from] = to;
			}
		}
	}
}
void dfs2(int from, int root) noexcept {
	top[from] = root;
	dfn[from] = ++ stamp;
	rnk[stamp] = from;
	if (son[from] == -1 ) {
		return;
	}
	dfs2(son[from], root);
	for (int ed = head[from]; ed; ed = edge[ed].next) {
		int to = edge[ed].to;
		if (to != son[from] && to != fa[from]) {
			dfs2(to, to);
		}
	}
}
void build(int root) noexcept {
	dep[root] = 1;
	stamp = 0;
	dfs1(root);
	dfs2(root,root);
}

void Solution() noexcept {
	int n, now, cas;
	cin >> n >> now >> cas;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);

	auto lca = [&](int a, int b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		return a;
	};

	auto jump = [&](int now, int cnt) {
		while (1) {
			auto need = dfn[now] - dfn[top[now]] + 1;
			if (cnt < need) {
				break;
			}
			cnt -= need;
			now = fa[top[now]];
		}
		return rnk[dfn[now] - cnt];
	};
	while (cas --) {
		int tag, cnt;
		cin >> tag >> cnt;
		int dad = lca(now, tag);
		int ls = dep[now] - dep[dad], rs = dep[tag] - dep[dad];
		if (ls + rs <= cnt) {
			now = tag;
		} else {
			if (tag == dad) {
				now = jump(now, cnt);
			} else if (now == dad) {
				now = jump(tag, ls + rs - cnt);
			} else {
				if (ls <= cnt) {
					now = dad;
					cnt -= ls;
					if (cnt) {
						now = jump(tag, rs - cnt);
					}
				} else {
					now = jump(now, cnt);
				}
			}
		}
		cout << now << ' ';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}