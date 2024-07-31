/* P3178 [HAOI2015]树上操作 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES cout << "YES\n"
#define NO cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e5 + 10;

vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int top[N], son[N], siz[N], dep[N], dfn[N], rnk[N], fa[N];
int stamp = 0;
ll w[N];
int rot = 0;

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
	rnk[stamp] = from;
	if (son[from] == -1) return;
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != son[from] && to != fa[from]) {
			dfs2(to, to);
		}
	}
}
void build(int root) {
	rot = root;
	memset(dep, -1, sizeof dep);
	dep[root] = stamp = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	ll val, lz;
} seg[N << 2];

void down(int l, int r, int id) {
	auto &d = seg[id].lz;
	if (d == 0) return;
	int mid = l + ((r - l) >> 1);
	seg[id * 2].val += (mid - l + 1) * d;
	seg[id * 2 + 1].val += (r - mid) * d;
	seg[id * 2].lz += d;
	seg[id * 2 + 1].lz += d;
	d = 0;
}
void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = w[rnk[l]];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void add(int l, int r, int id, int al, int ar, ll d) {
	if (l == al && r == ar) {
		seg[id].val += (r - l + 1) * d;
		seg[id].lz += d;
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
void add(int l, int r, int id, int tag, ll d) {
	if (l == r) {
		seg[id].val += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (tag <= mid) {
			add(l, mid, id * 2, tag, d);
		} else {
			add(mid + 1, r, id * 2 + 1, tag, d);
		}
		rise(id);
	}
}
ll query(int l, int r, int id, int ql, int qr) {
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

void Solution() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i) {
		cin >> w[i];
	}
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);
	build(1, n, 1);

	auto opt1 = [&](int x, int d) {
		add(1, n, 1, dfn[x], d);
	};
	auto opt2 = [&](int x, int d) {
		add(1, n, 1, dfn[x], dfn[x] + siz[x] - 1, d);
	};
	auto opt3 = [&](int x) {
		ll ret = 0;
		while (top[x] != rot) {
			ret += query(1, n, 1, dfn[top[x]], dfn[x]);
			x = fa[top[x]];
		}
		ret += query(1, n, 1, dfn[rot], dfn[x]);
		return ret;
	};
	
	while (q --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x; ll d;
			cin >> x >> d;
			opt1(x, d);
		} else if (opt == 2) {
			int x; ll d;
			cin >> x >> d;
			opt2(x, d);
		} else {
			int x;
			cin >> x;
			cout << opt3(x) << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}