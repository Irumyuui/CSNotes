/* File: P2590 [ZJOI2008]树的统计 */
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

const int N = 5e5 + 10;
vector<int> edge[N];

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int son[N], fa[N], dfn[N], dep[N], siz[N], top[N], rnk[N];
int stamp = 0;

int n;
int w[N];

void dfs1(int from) {
	siz[from] = 1;
	son[from] = -1;
	for (auto to : edge[from]) {
		if (dep[to] == -1) {
			fa[to] = from;
			dep[to] = dep[from] + 1;
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
	rnk[dfn[from]] = from;
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

struct Info {
	int sum, max;
} seg[N << 2];

void rise(int id) {
	seg[id].max = max(seg[id * 2].max, seg[id * 2 + 1].max);
	seg[id].sum = seg[id * 2].sum + seg[id * 2 + 1].sum;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].sum = seg[id].max = w[rnk[l]];
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void change(int l, int r, int id, int tag, int d) {
	if (l == r) {
		seg[id].sum = seg[id].max = d;
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			change(l, mid, id * 2, tag, d);
		} else {
			change(mid + 1, r, id * 2 + 1, tag, d);
		}
		rise(id);
	}
}

int query_max(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].max;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query_max(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query_max(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return max({
				query_max(l, mid, id * 2, ql, mid),
				query_max(mid + 1, r, id * 2 + 1, mid + 1, qr)
			});
		}
	}
}
int query_sum(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].sum;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query_sum(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query_sum(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query_sum(l, mid, id * 2, ql, mid) + query_sum(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int QMax(int a, int b) {
	int ret = -inf<int>;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		ret = max(ret, query_max(1, n, 1, dfn[top[a]], dfn[a]));
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	ret = max(ret, query_max(1, n, 1, dfn[a], dfn[b]));
	return ret;
}
int QSum(int a, int b) {
	int ret = 0;
	while (top[a] != top[b]) {
		if (dep[top[a]] < dep[top[b]]) {
			swap(a, b);
		}
		ret += query_sum(1, n, 1, dfn[top[a]], dfn[a]);
		a = fa[top[a]];
	}
	if (dep[a] > dep[b]) {
		swap(a, b);
	}
	ret += query_sum(1, n, 1, dfn[a], dfn[b]);
	return ret;
}
void Change(int id, int d) {
	change(1, n, 1, dfn[id], d);
}

void Solution() {
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	for (int i = 1; i <= n; ++ i) {
		cin >> w[i];
	}
	
	build(1);
	build(1, n, 1);
	
	int q;
	cin >> q;
	while (q --) {
		string opt;
		cin >> opt;
		if (opt == "QMAX") {
			int a, b;
			cin >> a >> b;
			cout << QMax(a, b) << '\n';
		} else if (opt == "QSUM") {
			int a, b;
			cin >> a >> b;
			cout << QSum(a, b) << '\n';
		} else {
			int x, d;
			cin >> x >> d;
			Change(x, d);
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}