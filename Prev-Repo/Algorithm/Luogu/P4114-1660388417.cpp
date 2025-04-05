/* P4114 Qtree1 */
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
struct Edge {
	int to, w, id;
};
vector<Edge> edge[N];
void add_edge(int from, int to, int w, int id) {
	edge[from].emplace_back(Edge{to, w, id});
	edge[to].emplace_back(Edge{from, w, id});
}

int son[N], dfn[N], dep[N], fa[N], siz[N], top[N], rnk[N];
int ernk[N], w[N];
int stamp = 0;

void dfs1(int from, int ew, int eid) {
	ernk[eid] = from;
	w[from] = ew;
	siz[from] = 1;
	son[from] = -1;
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
		if (to != son[from] && to != fa[from]) {
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
	int val;
} seg[N << 2];
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

void change(int l, int r, int id, int tag, int d) {
	if (l == r) {
		seg[id].val = d;
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
			return max(query(l, mid, id * 2, ql, mid), query(mid + 1, r, id * 2 + 1, mid + 1, qr));
		}
	}
}

void Solution() {
	int n;
	cin >> n;
	for (int i = 1; i < n; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		add_edge(from, to, w, i);
	}
	
	build(1);
	build(1, n, 1);

	#ifndef ONLINE_JUDGE
		for (int i = 1; i <= n; ++ i) {
			debug(i, dfn[i], ernk[i], w[i]);
		}
		for (int i = 1; i <= n; ++ i) {
			debug(query(1, n, 1, dfn[i], dfn[i]));
		}
		cerr << '\n';
	#endif

	auto Change = [&](int x, int d) {
		change(1, n, 1, dfn[ernk[x]], d);
	};
	auto Query = [&](int a, int b) {
		if (a == b) return 0;
		int ret = -inf<int>;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			ret = max(ret, query(1, n, 1, dfn[top[a]], dfn[a]));
			a = fa[top[a]];

			debug(ret);
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		if (dep[a] < dep[b]) {
			debug(dfn[a] + 1, dfn[b]);
			debug(query(1, n, 1, dfn[a] + 1, dfn[b]));
			ret = max(ret, query(1, n, 1, dfn[a] + 1, dfn[b]));
		}
		debug(ret);
		return ret;
	};

	while (true) {
		string opt;
		cin >> opt;
		if (opt == "DONE") {
			break;
		} else if (opt == "CHANGE") {
			int x, d;
			cin >> x >> d;
			Change(x, d);
		} else {
			int a, b;
			cin >> a >> b;
			cout << Query(a, b) << '\n';
		}

		#ifndef ONLINE_JUDGE
			for (int i = 1; i <= n; ++ i) {
				debug(query(1, n, 1, dfn[i], dfn[i]));
			}
			debug(query(1, n, 1, 1, n));
			cerr << '\n';
		#endif
	}

	#ifndef ONLINE_JUDGE
		debug(query(1, n, 1, 2, 3));
	#endif
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}