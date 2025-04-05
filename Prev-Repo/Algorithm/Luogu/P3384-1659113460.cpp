/* File: 树链剖分 */
#include <bits/stdc++.h>
using namespace std;

/* using fmtlib */
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

using ll = long long;

const int N = 4e5 + 10;
vector<int> edge[N];
int son[N], siz[N], dep[N], fa[N], dfn[N], top[N], rnk[N], stamp = 0;
ll w[N];

int n, m, root, mod;

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

void dfs1(int from) {
	siz[from] = 1;
	son[from] = -1;
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
	top[from] = root;
	dfn[from] = ++ stamp;
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
	dep[root] = 1;
	dfs1(root);
	dfs2(root, root);
}

struct Node {
	ll val, d;
} seg[N];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void down(int l, int r, int id) {
	auto &d = seg[id].d;
	if (!d) return;
	int mid = l + ((r - l) >> 1);
	seg[id * 2].val = ((mid - l + 1) * d + seg[id * 2].val) % mod;
	seg[id * 2 + 1].val = ((r - mid) * d + seg[id * 2 + 1].val) % mod;
	seg[id * 2].d += d;
	seg[id * 2 + 1].d += d;
	d = 0;
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
void modify(int l, int r, int id, int ml, int mr, ll d) {
	if (l == ml && r == mr) {
		seg[id].val = (seg[id].val + (r - l + 1) * d) % mod;
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
ll query(int l ,int r, int id, int ql, int qr) {
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
			return (query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr)) % mod;
		}
	}
}

void opt1(int a, int b, ll d) {
	while (top[a] != top[b]) {
		// int l = 0, r = 0;
		// if (dep[top[a]] > dep[top[b]]) {
		// 	l = dfn[top[a]], r = dfn[a];
		// 	modify(1, n, 1, dfn[top[a]], dfn[a], d);
		// 	a = fa[top[a]];
		// } else {
		// 	l = dfn[top[b]], r = dfn[b];
		// 	modify(1, n, 1, dfn[top[b]], dfn[b], d);
		// 	b = fa[top[b]];
		// }
		
		// debug(l, r);
		
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		modify(1, n, 1, dfn[top[a]], dfn[a], d);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	
	debug(dfn[a], dfn[b]);

	modify(1, n, 1, dfn[a], dfn[b], d);
}
ll opt2(int a, int b) {
	ll ret = 0;
	while (top[a] != top[b]) {
		// int l = 0, r = 0;

		// if (dep[top[a]] > dep[top[b]]) {
		// 	l = dfn[top[a]], r = dfn[a];
		// 	ret = (ret + query(1, n, 1, dfn[top[a]], dfn[a])) % mod;
		// 	a = fa[top[a]];
		// } else {
		// 	l = dfn[top[b]], r = dfn[b];
		// 	ret = (ret + query(1, n, 1, dfn[top[b]], dfn[b])) % mod;
		// 	b = fa[top[b]];
		// }
		
		// debug(l, r);

		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		ret = (ret + query(1, n, 1, dfn[top[a]], dfn[a])) % mod;
		a = fa[top[a]];

	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}

	debug(dfn[a], dfn[b]);
	
	ret = (ret + query(1, n, 1, dfn[a], dfn[b])) % mod;
	return ret;
}
void opt3(int id, ll x) {
	debug(dfn[id], dfn[id] + siz[id] - 1);
	
	modify(1, n, 1, dfn[id], dfn[id] + siz[id] - 1, x);
}
ll opt4(int id) {
	debug(dfn[id], dfn[id] + siz[id] - 1);

	return query(1, n, 1, dfn[id], dfn[id] + siz[id] - 1);
}

void Solution() {
	cin >> n >> m >> root >> mod;
	vector<ll> _w(n + 1);
	for (int i = 1; i <= n; ++ i) {
		cin >> _w[i];
		// cin >> w[i];
	}
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(root);
	for (int i = 1; i <= n; ++ i) {
		w[i] = _w[rnk[i]];
	}

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			cerr << rnk[i] << ' ';
		}
		cerr << '\n';
	#endif 

	build(1, n, 1);
	for (int _ = 1; _ <= m; ++ _) {


		int opt;
		cin >> opt;
		debug(_, opt);
		if (opt == 1) {
			int a, b; ll d;
			cin >> a >> b >> d;
			opt1(a, b, d);
		} else if (opt == 2) {
			int a, b;
			cin >> a >> b;
			cout << opt2(a, b) << '\n';
		} else if (opt == 3) {
			int x; ll d;
			cin >> x >> d;
			opt3(x, d);
		} else {
			int x;
			cin >> x;
			cout << opt4(x) << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}