#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#define cauto const auto
#define all(x) std::begin(x), std::end(x)
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#if __cplusplus >= 202002L
	namespace rgs = ranges;
#endif
template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 2e5 + 10;
vector<int> edge[N];
int vw[N];
void add_edge(int from, int to) {
	edge[from].emplace_back(to);
	edge[to].emplace_back(from);
}

int dep[N], fa[N][22], top[N], dfn[N], son[N], siz[N], rnk[N];
int stamp = 0;

void dfs1(int from) {
	for (int i = 1; (1 << i) <= dep[from]; i ++) {
		fa[from][i] = fa[fa[from][i - 1]][i - 1];
	}
	son[from] = -1;
	siz[from] = 1;
	for (auto to : edge[from]) {
		if (dep[to] == -1) {
			dep[to] = dep[from] + 1;
			fa[to][0] = from;
			dfs1(to);
			siz[from] += siz[to];
			if (son[from] == -1 || siz[to] > siz[son[from]])
				son[from] = to;
		}
	}
}
void dfs2(int from, int root) {
	top[from] = root;
	dfn[from] = ++ stamp;
	rnk[stamp] = from;
	if (son[from] == -1) return;
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != son[from] && to != fa[from][0]) {
			dfs2(to, to);
		}
	}
}

void build(int root) {
	memset(dep, -1, sizeof dep);
	dep[1] = 1;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	int val;
	Info(int v = inf<int>) : val(v) {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info{min(a.val, b.val)};
	}
};
struct Node {
	Info val;
	int lz;
} seg[N * 4];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void update(int id, int d) {
	seg[id].val = d;
	seg[id].lz = d;
}
void down(int l, int r, int id) {
	if (seg[id].lz == -1) return;
	update(id * 2, seg[id].lz);
	update(id * 2 + 1, seg[id].lz);
	seg[id].lz = -1;
}

void build(int l, int r, int id) {
	seg[id].lz = -1;
	if (l == r) {
		seg[id].val = vw[rnk[l]];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}
void modify(int l, int r, int id, int ml, int mr, int d) {
	if (l == ml && r == mr) {
		update(id, d);
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, d);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, d);
		} else {
			modify(l, mid, id * 2, ml, mid, d);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, d);
		}
		rise(id);
	}
}
Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + (r - l) / 2;
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int lca(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) swap(a, b);
		a = fa[top[a]][0];
	}
	if (dep[a] > dep[b]) swap(a, b);
	return a;
}

int rise(int u, int d) {
	debug(u, d);
	for (int i = 20; i >= 0; i --) {
		debug(u, fa[u][i]);
		if (d & (1 << i)) {
			u = fa[u][i];
		}
	}
	return u;
}

auto Solve() -> void {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		add_edge(u, v);
	}
	for (int i = 1; i <= n; i ++) {
		cin >> vw[i];
	}

	debug(1);
	build(1);
	build(1, n, 1);

	auto Modify = [&](int a, int b, int d) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) swap(a, b);
			modify(1, n, 1, dfn[top[a]], dfn[a], d);
			a = fa[top[a]][0];
		}
		if (dep[a] > dep[b])
			swap(a, b);
		modify(1, n, 1, dfn[a], dfn[b], d);
	};

	int root;
	cin >> root;
	for (int _ = 1; _ <= q; _ ++) {
		int opt;
		cin >> opt;
		debug(_, opt);
		if (opt == 1) {
			cin >> root;
		} else if (opt == 2) {
			int u, v, d;
			cin >> u >> v >> d;
			Modify(u, v, d);
		} else {
			int u;
			cin >> u;
			if (root == u) {
				cout << query(1, n, 1, 1, n).val << '\n';
			} else if (!(dfn[u] <= dfn[root] && dfn[root] <= dfn[u] + siz[u] - 1)) {
				cout << query(1, n, 1, dfn[u], dfn[u] + siz[u] - 1).val << '\n';
			} else {
				int v = rise(root, dep[root] - dep[u] - 1);
				debug(v, dfn[root], dfn[u]);
				int l = dfn[v], r = dfn[v] + siz[v] - 1;
				Info ret;
				if (l - 1 >= 1) {
					ret = ret + query(1, n, 1, 1, l - 1);
				}
				if (r + 1 <= n) {
					ret = ret + query(1, n, 1, r + 1, n);
				}
				// assert(ret.val != inf<int>);
				cout << ret.val << '\n';
			}
		}
	}
}

auto main() -> int32_t {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Solve();
	}
}