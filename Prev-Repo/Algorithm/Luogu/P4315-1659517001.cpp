/* P4315 月下“毛景树” */
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e5 + 10;

int n;

struct Edge {
	int to, w, id;
};
vector<Edge> edge[N];
void add_edge(int from, int to, int w, int id) {
	edge[from].push_back({to, w, id});
	edge[to].push_back({from, w, id});
}

int son[N], dep[N], siz[N], fa[N], top[N], dfn[N], rnk[N], ernk[N];
int w[N];
int stamp = 0;

void dfs1(int from, int ew, int eid) {
	son[from] = -1;
	siz[from] = 1;
	w[from] = ew;
	ernk[eid] = from;
	for (auto [to, w, id] : edge[from]) {
		if (dep[to] == -1) {
			dep[to] = dep[from] + 1;
			fa[to] = from;
			dfs1(to, w, id);
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
	for (auto [to, _, __] : edge[from]) {
		if (to != fa[from] && to != son[from]) {
			dfs2(to, to);
		}
	}
}
void build(int root) {
	memset(dep, -1, sizeof dep);
	dep[root] = 0;
	dfs1(root, 0, 0);
	dfs2(root, root);
}

struct Info {
	int val, lzc, lza;
	bool mkc;
} seg[N << 2];

void down(int id) {
	if (seg[id].mkc) {
		auto &lzc = seg[id].lzc;
		seg[id * 2].lza = seg[id * 2 + 1].lza = 0;
		seg[id * 2].val = seg[id * 2 + 1].val = seg[id * 2].lzc = seg[id * 2 + 1].lzc = lzc;
		seg[id * 2].mkc = seg[id * 2 + 1].mkc = true;
		seg[id].mkc = false;
	}
	auto &d = seg[id].lza;
	if (d == 0) return;
	seg[id * 2].lza += d;
	seg[id * 2 + 1].lza += d;
	seg[id * 2].val += d;
	seg[id * 2 + 1].val += d;
	d = 0;
}

void rise(int id) {
	seg[id].val = max(seg[id * 2].val, seg[id * 2 + 1].val);
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

void modify(int l, int r, int id, int ml, int mr, int val) {
	if (l == ml && r == mr) {
		seg[id].val = val;
		seg[id].lza = 0;
		seg[id].lzc = val;
		seg[id].mkc = true;
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

void change(int l, int r, int id, int tag, int val) {
	if (l == r) {
		seg[id].val = val;
		seg[id].lza = 0;
		seg[id].lzc = val;
		seg[id].mkc = true;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (tag <= mid) {
			change(l, mid, id * 2, tag, val);
		} else {
			change(mid + 1, r, id * 2 + 1, tag, val);
		}
		rise(id);
	}
}

void add(int l, int r, int id, int al, int ar, int d) {
	if (l == al && r == ar) {
		seg[id].val += d;
		seg[id].lza += d;
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
			return max(query(l, mid, id * 2, ql, mid), query(mid + 1, r, id * 2 + 1, mid + 1, qr));
		}
	}
}

void Change(int id, int val) {
	change(1, n, 1, dfn[ernk[id]], val);
}
void Cover(int a, int b, int val) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		modify(1, n, 1, dfn[top[a]], dfn[a], val);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	if (dep[a] < dep[b]) {
		modify(1, n, 1, dfn[a] + 1, dfn[b], val);
	}
}

void Add(int a, int b, int val) {
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		add(1, n, 1, dfn[top[a]], dfn[a], val);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	if (dep[a] < dep[b]) {
		add(1, n, 1, dfn[a] + 1, dfn[b], val);
	}
}

int Max(int a, int b) {
	int ret = -inf<int>;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		ret = max(ret, query(1, n, 1, dfn[top[a]], dfn[a]));
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	if (dep[a] < dep[b]) {
		ret = max(ret, query(1, n, 1, dfn[a] + 1, dfn[b]));
	}
	return ret;
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b, w;
		cin >> a >> b >> w;
		add_edge(a, b, w, i);
	}
	build(1);
	build(1, n, 1);
	while (1) {
		string opt;
		cin >> opt;
		if (opt == "Change") {
			int k, w;
			cin >> k >> w;
			Change(k, w);
		} else if (opt == "Cover") {
			int u, v, w;
			cin >> u >> v >> w;
			Cover(u, v, w);
		} else if (opt == "Add") {
			int u, v, w;
			cin >> u >> v >> w;
			Add(u, v, w);
		} else if (opt == "Max") {
			int u, v;
			cin >> u >> v;
			cout << Max(u, v) << '\n';
		} else {
			return;
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}