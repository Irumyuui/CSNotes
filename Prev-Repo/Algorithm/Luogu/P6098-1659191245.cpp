/* File: P6098 [USACO19FEB]Cow Land G */
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;

int n, q;

vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int son[N], dep[N], dfn[N], rnk[N], top[N], siz[N], fa[N];
int stamp = 0;
int w[N], _w[N];

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
	rnk[stamp] = from;
	top[from] = root;
	w[dfn[from]] = _w[from];
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
	int val;
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val ^ seg[id * 2 + 1].val;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = w[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int pos, int d) {
	if (l == r) {
		seg[id].val = d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (pos <= mid) {
			change(l, mid, id * 2, pos, d);
		} else {
			change(mid + 1, r, id * 2 + 1, pos, d);
		}
		rise(id);
	}
}
int query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) ^ query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int query(int a, int b) {
	int ret = 0; 
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		ret ^= query(1, n, 1, dfn[top[a]], dfn[a]);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	ret ^= query(1, n, 1, dfn[a], dfn[b]);
	return ret;
}

void Solution() {
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i) {
		cin >> _w[i];
	}
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);
	build(1, n, 1);
	while (q --) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, d;
			cin >> x >> d;
			change(1, n, 1, dfn[x], d);
		} else {
			int a, b;
			cin >> a >> b;
			cout << query(a, b) << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}