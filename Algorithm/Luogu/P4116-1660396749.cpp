/* P4116 Qtree3 */
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
vector<int> edge[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int son[N], dfn[N], fa[N], top[N], siz[N], dep[N], rnk[N];
int stamp = 0;

void dfs1(int from) {
	siz[from] = 1;
	son[from] = -1;
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
	dep[root] = stamp = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	int val;
	int lz;
} seg[N << 2];

void down(int l, int r, int id) {
	auto &c = seg[id].lz;
	if (c == 0) return;
	int mid = l + ((r - l) >> 1);
	seg[id * 2].val = (mid - l + 1) - seg[id * 2].val;
	seg[id * 2 + 1].val = (r - mid) - seg[id * 2 + 1].val;
	seg[id * 2].lz ^= 1;
	seg[id * 2 + 1].lz ^= 1;
	c = 0;
} 
void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void modify(int l, int r, int id, int ml, int mr) {
	if (l == ml && r == mr) {
		seg[id].val = (r - l + 1) - seg[id].val;
		seg[id].lz ^= 1;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr);
		} else {
			modify(l, mid, id * 2, ml, mid);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr);
		}
		rise(id);
	}
}

void change(int l, int r, int id, int tag) {
	if (l == r) {
		seg[id].val ^= 1;
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (tag <= mid) {
			change(l, mid, id * 2, tag);
		} else {
			change(mid + 1, r, id * 2 + 1, tag);
		}
		rise(id);
	}
}

int query(int l, int r, int id, int ql, int qr) {
	if (seg[id].val == 0) {
		return -1;
	}
	if (l == ql && r == qr) {
		if (l == r) {
			return rnk[l];
		} else {
			int mid = l + ((r - l) >> 1);
			down(l, r, id);
			int ret = query(l, mid, id * 2, ql, mid);
			if (ret == -1) {
				ret = query(mid + 1, r, id * 2 + 1, mid + 1, qr);
			}
			return ret;
		}
	} else {
		int mid = l + ((r - l) >> 1);
		down(l, r, id);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			int ret = query(l, mid, id * 2, ql, mid);
			if (ret == -1) {
				ret = query(mid + 1, r, id * 2 + 1, mid + 1, qr);
			}
			return ret;
		}
	}
}

void Solution() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i < n; ++ i) {
		int from, to;
		cin >> from >> to;
		add_edge(from, to);
	}
	build(1);

	auto Query = [&](int x) {
		int ret = -1;
		while (top[x] != 1) {
			int tmp = query(1, n, 1, dfn[top[x]], dfn[x]);
			if (tmp != -1) {
				ret = tmp;
			}
			x = fa[top[x]];
		}
		int tmp = query(1, n, 1, 1, dfn[x]);
		if (tmp != -1) {
			ret = tmp;
		}
		return ret;
	};

	while (q --) {
		int opt, x;
		cin >> opt >> x;
		if (opt == 0) {
			change(1, n, 1, dfn[x]);
		} else {
			cout << Query(x) << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
	return 0;
}