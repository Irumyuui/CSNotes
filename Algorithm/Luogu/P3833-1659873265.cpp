/* P3833 [SHOI2012]魔法树 */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

int n;

const int N = 1e5 + 10;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int dfn[N], son[N], siz[N], fa[N], top[N], dep[N];
int stamp = 0;

void dfs1(int from) {
	son[from] = -1;
	siz[from] = 1;
	for (auto to : edge[from]) {
		if (dep[to] == -1) {
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
void dfs2(int from, int root) {
	top[from] = root;
	dfn[from] = ++ stamp;
	if (son[from] == -1) {
		return;
	}
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != fa[from] && to != son[from]) {
			dfs2(to, to);
		}
	}
}
void build(int root) {
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	ll val, lza;
} seg[N << 2];
void down(int l, int r, int id) {
	auto &d = seg[id].lza;
	if (d == 0) return;
	int mid = l + ((r - l) >> 1);
	seg[id * 2].val += (mid - l + 1) * d;
	seg[id * 2 + 1].val += (r - mid) * d;
	seg[id * 2].lza += d;
	seg[id * 2 + 1].lza += d;
	d = 0;
}
void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void add(int l, int r, int id, int al, int ar, auto d) {
	if (l == al && r == ar) {
		seg[id].val += (r - l + 1) * d;
		seg[id].lza += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (ar <= mid) {
			add(l, mid, id * 2, al, ar, d);
		} else if (al > mid) {
			add(mid + 1, r, id * 2 + 1, al, ar, d);
		} else {
			add(l, mid, id * 2, al, mid, d);
			add(mid + 1, r, id * 2 + 1, mid + 1, ar, d);
		}
		rise(id);
	}
}
auto query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
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

void Add(int a, int b, auto d) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		add(1, n, 1, dfn[top[a]], dfn[a], d);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	add(1, n, 1, dfn[a], dfn[b], d);
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(0);
	int q;
	cin >> q;
	while (q --) {
		char opt;
		cin >> opt;
		if (opt == 'A') {
			int a, b;
			ll w;
			cin >> a >> b >> w;
			Add(a, b, w);
		} else {
			int x;
			cin >> x;

			#ifndef ONLINE_JUDGE
				debug(dfn[x], dfn[x] + siz[x] - 1);
			#endif

			cout << query(1, n, 1, dfn[x], dfn[x] + siz[x] - 1) << '\n';
		}
	}

	#ifndef ONLINE_JUDGE
		for (int i = 0; i < n; ++ i) {
			debug(query(1, n, 1, dfn[i], dfn[i]));
		}
		debug(query(1, n, 1, 1, n));
	#endif
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}