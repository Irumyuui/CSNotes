/* File: P4092 [HEOI2016 TJOI2016]树 */
#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 10;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int dep[N], dfn[N], son[N], fa[N], siz[N], top[N], rnk[N];
int stamp = 0;

int n, q;

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
	dfn[from] = ++ stamp;
	top[from] = root;
	rnk[stamp] = from;
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
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root);
	dfs2(root, root);
}

// max node
struct Info {
	int val, lazy;
} seg[N << 2];

void rise(int id) {
	seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val);
}
void down(int id) {
	auto &lz = seg[id].lazy;
	seg[id * 2].val = max(seg[id * 2].val, lz);
	seg[id * 2 + 1].val = max(seg[id * 2 + 1].val, lz);
	seg[id * 2].lazy = max(seg[id * 2].lazy, lz);
	seg[id * 2 + 1].lazy = max(seg[id * 2 + 1].lazy, lz);
	lz = 0;
}

void modify(int l, int r, int id, int ml, int mr, int d) {
	if (l == ml && r == mr) {
		seg[id].val = max(seg[id].val, d);
		seg[id].lazy = max(seg[id].lazy, d);
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, d);
		} else if (ml > mid) {
			modify(mid + 1, r , id * 2 + 1, ml, mr, d);
		} else {
			modify(l, mid, id * 2, ml, mid, d);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, d);
		}
		rise(id);
	}
}

int ask(int l, int r, int id, int sl, int sr) {
	if (l == sl && r == sr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (sr <= mid) {
			return ask(l, mid, id * 2, sl, sr);
		} else if (sl > mid) {
			return ask(mid + 1, r, id * 2 + 1, sl, sr);
		} else {
			return max(
				ask(l, mid, id * 2, sl, mid),
				ask(mid + 1, r, id * 2 + 1, mid + 1, sr)
			);
		}
	}
}

int ask(int l, int r, int id, int pos) {
	if (l == r) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (pos <= mid) {
			return ask(l, mid, id * 2, pos);
		} else {
			return ask(mid + 1, r, id * 2 + 1, pos);
		}
	}
}

void Solution() {
	cin >> n >> q;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}

	build(1);

	modify(1, n, 1, 1, n, 1);

	while (q --) {
		char opt;
		cin >> opt;
		if (opt == 'C') {
			int x;
			cin >> x;
			modify(1, n, 1, dfn[x], dfn[x] + siz[x] - 1, dfn[x]);
		} else {
			int x;
			cin >> x;
			cout << rnk[ask(1, n, 1, dfn[x])] << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}