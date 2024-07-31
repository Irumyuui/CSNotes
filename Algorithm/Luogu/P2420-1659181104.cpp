/* File: P2420 让我们异或吧 */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 1e6 + 10;
vector<pair<int,int>> edge[N];

int top[N], siz[N], fa[N], dep[N], son[N], dfn[N];
int stamp = 0;
int w[N], _w[N];

void add_edge(int from, int to, int w) {
	edge[from].push_back({to, w});
	edge[to].push_back({from, w});
}

void dfs1(int from, int w) {
	siz[from] = 1;
	son[from] = -1;
	_w[from] = w;
	for (auto [to, _w] : edge[from]) {
		if (!dep[to]) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to, _w);
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
	w[dfn[from]] = _w[from];
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

int n;
int seg[N << 2];

void build(int l, int r, int id) {
	if (l == r) {
		seg[id] = w[l];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		seg[id] = seg[id * 2] ^ seg[id * 2 + 1];
	}
}
int query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id];
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
	if (dep[a] < dep[b]) {
		ret ^= query(1, n, 1, dfn[a] + 1, dfn[b]);
	}
	return ret;
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b, w;
		cin >> a >> b >> w;
		add_edge(a, b, w);
	}
	build(1);
	build(1, n, 1);

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			cerr << _w[i] << ' ';
		}
		cerr << '\n';
		for (int i = 1; i <= n; ++ i) {
			cerr << w[i] << ' ';
		}
		cerr << '\n';

		debug(1);

		for (int i = 1; i <= n; ++ i) {
			cerr << query(1, n, 1, i, i) << ' ';
		}
		cerr << '\n';

	#endif
	
	int q;
	cin >> q;
	while (q --) {
		int a, b;
		cin >> a >> b;
		cout << query(a, b) << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}