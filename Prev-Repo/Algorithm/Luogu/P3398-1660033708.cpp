/* P3398 仓鼠找 sugar */
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

int son[N], fa[N], dep[N], dfn[N], top[N], siz[N];
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
	dep[root] = stamp = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	int val, lz;
} seg[N << 2];

void down(int id) {
	auto &d = seg[id].lz;
	if (d == 0) return;
	seg[id * 2].val += d;
	seg[id * 2 + 1].val += d;
	seg[id * 2].lz += d;
	seg[id * 2 + 1].lz += d;
	d = 0;
}
void rise(int id) {
	seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val);
}

void add(int l, int r, int id, int al, int ar, int d) {
	debug(l, r, al, ar);
	if (l == al && r == ar) {
		seg[id].val += d;
		seg[id].lz += d;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
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
ll query(int l, int r, int id, int ql, int qr) {
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
			return max(query(l, mid, id * 2, ql, mid), query(mid + 1, r, id * 2 + 1, mid + 1, qr));
		}
	}
}

void Solution() {
	int n, q;
	cin >> n >> q;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);
	
	auto Add = [&](int a, int b, int d) {
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
	};
	auto Query = [&](int a, int b) -> bool {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			if (query(1, n, 1, dfn[top[a]], dfn[a])) {
				return true;
			}
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		return query(1, n, 1, dfn[a], dfn[b]) != 0;
	};

	debug(1);
	
	while (q --) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		Add(a, b, 1);

		debug(2);

		if (Query(c, d)) {
			cout << "Y\n";
		} else {
			cout << "N\n";
		}

		debug(3);

		Add(a, b, -1);
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}