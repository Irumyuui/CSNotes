/* P4374 [USACO18OPEN]Disruption P */
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

const int N = 1e6 + 10;
struct Edge {
	int to, id;
};
vector<Edge> edge[N];
void add_edge(int from, int to, int id) {
	edge[from].push_back({to, id});
	edge[to].push_back({from, id});
}

int n;
int son[N], siz[N], dep[N], dfn[N], rnk[N], top[N], fa[N];
int ernk[N];
int stamp = 0;
void dfs1(int from, int eid) {
	ernk[eid] = from;
	son[from] = -1;
	siz[from] = 1;
	for (auto [to, id] : edge[from]) {
		if (dep[to] == -1) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to, id);
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
	if (son[from] == -1) {
		return;
	}
	dfs2(son[from], root);
	for (auto [to, _] : edge[from]) {
		if (to != son[from] && to != fa[from]) {
			dfs2(to, to);
		}
	}
}
void build(int root) {
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root, 0);
	dfs2(root, root);
}

struct Info {
	int val, lz;
	Info() : val(inf<int>), lz(inf<int>) {}
} seg[N << 2];
void rise(int id) {
	seg[id].val = min(seg[id * 2].val, seg[id * 2 + 1].val);
	debug(id * 2, seg[id * 2].val, id * 2 + 1, seg[id * 2 + 1].val);
}
void down(int id) {
	auto &lz = seg[id].lz;
	if (lz == inf<int>) {
		return;
	}
	seg[id * 2].val = min(seg[id * 2].val, lz);
	seg[id * 2 + 1].val = min(seg[id * 2 + 1].val, lz);
	seg[id * 2].lz = min(seg[id * 2].lz, lz);
	seg[id * 2 + 1].lz = min(seg[id * 2 + 1].lz, lz);
	lz = inf<int>;
}
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = inf<int>;
		seg[id].lz = inf<int>;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}

	debug(seg[id].val);
}
void modify(int l, int r, int id, int ml, int mr, int val) {	
	assert(l <= r);
	assert(ml <= mr);
	
	if (l == ml && r == mr) {
		seg[id].val = min(seg[id].val, val);
		seg[id].lz = min(seg[id].lz, val);
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, val);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, val);
		} else {
			modify(l, mid, id * 2, ml, mid, val);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, val);
		}
		rise(id);
	}
}
int query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return min({
				query(l, mid, id * 2, ql, mid),
				query(mid + 1, r, id * 2 + 1, mid + 1, qr)
			});
		}
	}
}
int query(int l, int r, int id, int tag) {
	if (l == r) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (tag <= mid) {
			return query(l, mid, id * 2, tag);
		} else {
			return query(mid + 1, r, id * 2 + 1, tag);
		}
	}
}

void Modify(int a, int b, int d) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		modify(1, n, 1, dfn[top[a]], dfn[a], d);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	if (dep[a] < dep[b]) {
		modify(1, n, 1, dfn[a] + 1, dfn[b], d);
	}
}

void Solution() {
	int m;
	cin >> n >> m;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b, i);
	}
	build(1);
	build(1, n, 1);

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			debug(i, dfn[i], son[i], siz[i], fa[i]);
		}
		debug(1);
		for (int i = 1; i <= n; ++ i) {
			debug(query(1, n, 1, i));
		}
	#endif

	while (m --) {
		int a, b, w;
		cin >> a >> b >> w;
		Modify(a, b, w);
	} 
	for (int i = 1; i < n; ++ i) {
		int ret = query(1, n, 1, dfn[ernk[i]]);
		if (ret == inf<int>) ret = -1;
		cout << ret << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}