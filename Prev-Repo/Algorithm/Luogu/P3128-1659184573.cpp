/* File: P3128 [USACO15DEC]Max Flow P */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 4e5 + 10;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int son[N], dep[N], dfn[N], siz[N], fa[N], top[N], stamp = 0;

void dfs1(int from) {
	son[from] = -1;
	siz[from] = 1;
	for (auto to : edge[from]) {
		if (!dep[to]) {
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
	dfn[from] = ++ stamp;
	top[from] = root;
	if (son[from] == -1) {
		return;
	}
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != son[from] && to != fa[from]) {
			dfs2(to, to);
		}
	}
}

void build(int root) {
	dep[root] = 1;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	// max val
	int val, d;
} seg[N];
void down(int l, int r, int id) {
	auto &d = seg[id].d;
	if (d == 0) {
		return;
	}
	seg[id * 2].val += d; 
	seg[id * 2 + 1].val += d;
	seg[id * 2].d += d;
	seg[id * 2 + 1].d += d;
	d = 0;
}
void rise(int id) {
	seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val);
}
void modify(int l, int r, int id, int ml, int mr, int d) {
	if (l == ml && r == mr) {
		seg[id].val += d;
		seg[id].d += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, d);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, d);
		} else {
			modify(l, mid, id * 2, ml, mid, d); modify(mid + 1, r, id * 2 + 1, mid + 1, mr, d);
		}
		rise(id);
	}
}

int query(int l, int r, int id, int sl, int sr) {
	// assert(sl <= sr);
	debug(l, r, id);
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
			return max(query(l, mid, id * 2, sl, mid), query(mid + 1, r, id * 2 + 1, mid + 1, sr));
		}
	}
}

int n, k;
void change(int a, int b) {
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

	debug(dfn[a], dfn[b]);
	
	modify(1, n, 1, dfn[a], dfn[b], 1);
}

void Solution() {
	cin >> n >> k;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	
	debug(1);
	
	build(1);
	
	debug(2);
	
	while (k --) {
		int a, b;
		cin >> a >> b;
		change(a, b);
	}

	debug(3);

	cout << query(1, n, 1, 1, n);
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}