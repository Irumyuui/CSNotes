/* P3258 [JLOI2014]松鼠的新家 */
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

const int N = 1e6 + 10;
int n;
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int stamp = 0;
int son[N], siz[N], fa[N], dep[N], dfn[N], top[N];

void dfs1(int from) {
	son[from] = -1;
	siz[from] = 1;
	for (auto to : edge[from]) {
		if (dep[to] == -1) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to);
			siz[from] += siz[to];
			if (son[from] == -1 && siz[to] > siz[son[from]]) {
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
	stamp = 0;
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	int val, lz;
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

void add(int l, int r, int id, int al, int ar, int val) {
	if (l == al && r == ar) {
		seg[id].val += (r - l + 1) * val;
		seg[id].lz += val;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (ar <= mid) {
			add(l, mid, id * 2, al, ar, val);
		} else if (al > mid) {
			add(mid + 1, r, id * 2 + 1, al, ar, val);
		} else {
			add(l, mid, id * 2, al, mid, val);
			add(mid + 1, r, id * 2 + 1, mid + 1, ar, val);
		}
		rise(id);
	}
}

int query(int l, int r, int id, int ql, int qr) {
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
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, qr, id * 2 + 1, mid + 1, qr);
		}
	}
}

void Add(int a, int b) {
	add(1, n, 1, dfn[a], dfn[a], -1);
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		debug(a, dfn[top[a]], dfn[a]);
		add(1, n, 1, dfn[top[a]], dfn[a], 1);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) swap(a, b);
	debug(a, dfn[a], b, dfn[b]);
	add(1, n, 1, dfn[a], dfn[b], 1);
}

void Solution() {
	cin >> n;
	vector<int> a(n);
	for (auto &x : a) cin >> x;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			debug(i, dfn[i]);
		}
	#endif

	add(1, n, 1, dfn[a[0]], dfn[a[0]], 1);
	add(1, n, 1, dfn[a[n - 1]], dfn[a[n - 1]], -1);

	for (int i = 1; i < n; ++ i) {
		Add(a[i - 1], a[i]);
		
		#ifndef ONLINE_JUDGE
			cerr << a[i - 1] << ' ' << a[i] << '\n';
			for (int i = 1; i <= n; ++ i) {
				cerr << query(1, n, 1, dfn[i], dfn[i]) << ' ';
			}
			cerr << '\n';
			cerr << '\n';
		#endif
	}
	for (int i = 1; i <= n; ++ i) {
		cout << query(1, n, 1, dfn[i], dfn[i]) << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}