/* File: P3038 [USACO11DEC]Grass Planting G */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 1e5 + 10;
vector<pair<int,int>> edge[N];
int n, m;
void add_edge(int from, int to, int w) {
	edge[from].push_back({to, w});
	edge[to].push_back({from, w});
}

int son[N], dep[N], top[N], siz[N], fa[N], dfn[N];
int w[N], _w[N], stamp = 0;
void dfs1(int from, int W) {
	_w[from] = W;
	siz[from] = 1;
	son[from] = -1;
	for (auto [to, w] : edge[from]) {
		if (!dep[to]) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to, w);
			siz[from] += siz[to];
			if (son[from] == -1 || siz[to] > siz[son[from]]) {
				son[from] = to;
			}
		}
	}
}
void dfs2(int from, int root) {
	dfn[from] = ++ stamp;
	w[dfn[from]] = _w[from];
	top[from] = root;
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
	dep[root] = 1;
	dfs1(root, 0);
	dfs2(root, root);
}

struct {
	int val, d;
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void down(int l, int r, int id) {
	auto &d = seg[id].d;
	if (d == 0) {
		return;
	}
	int mid = l + ((r - l) >> 1);
	seg[id * 2].val += (mid - l + 1) * d;
	seg[id * 2 + 1].val += (r - mid) * d;
	seg[id * 2].d += d;
	seg[id * 2 + 1].d += d;
	d = 0;
}

void modify(int l, int r, int id, int ml, int mr, int d) {
	if (l == ml && r == mr) {
		seg[id].val += (r - l + 1) * d; 
		seg[id].d += d;
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

int query(int l, int r, int id, int sl, int sr) {
	if (l == sl && r == sr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (sr <= mid) {
			return query(l, mid, id * 2, sl, sr);			
		} else if (sl > mid) {
			return query(mid + 1, r, id * 2 + 1, sl, sr);
		} else {
			return query(l, mid, id * 2, sl, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, sr);
		}
	}
}

void opt1(int a, int b) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		debug(dfn[top[a]], dfn[a]);
		modify(1, n, 1, dfn[top[a]], dfn[a], 1);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	if (dep[a] < dep[b]) {
		modify(1, n, 1, dfn[a] + 1, dfn[b], 1);
	}
}

int opt2(int a, int b) {
	if (dep[a] < dep[b]) {
		swap(a, b);
	}
	return query(1, n, 1, dfn[a], dfn[a]);
}

void Solution() {
	cin >> n >> m;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b, 0);
	}
	build(1);

	debug(1);

	while (m --) {
		debug(m);
		char opt;
		cin >> opt;
		if (opt == 'P') {
			int a, b;
			cin >> a >> b;
			opt1(a, b);
		} else {
			int a, b;
			cin >> a >> b;
			cout << opt2(a, b) << '\n';
		}
	}	
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}