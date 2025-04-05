/* P2486 [SDOI2011]染色 */
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

const int N = 1e5 + 10;

vector<int> edge[N];
int fa[N], dep[N], dfn[N], rnk[N], siz[N], top[N], son[N];
int w[N];
int stamp = 0;

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

void build(int root) {
	function<void(int)> dfs1 = [&](int from) {
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
	};

	function<void(int,int)> dfs2 = [&](int from, int root) {
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
	};

	memset(dep, -1, sizeof dep);
	stamp = dep[root] = 0;
	dfs1(root);
	dfs2(root, root);
}

struct Info {
	int cnt, lc_c, rc_c;
	void init(int col) {
		cnt = 1;
		lc_c = rc_c = col;
	}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			a.cnt + b.cnt - (a.rc_c == b.lc_c),
			a.lc_c,
			b.rc_c
		};
	}
};
struct Node {
	Info val;
	int lz;
	Node() : lz(-1) {}
} seg[N << 2];

void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

void down(int id) {
	auto &c = seg[id].lz;
	if (c == -1) {
		return;
	}
	seg[id * 2].val.init(c);
	seg[id * 2 + 1].val.init(c);
	seg[id * 2].lz = seg[id * 2 + 1].lz = c;
	c = -1;
}

void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val.init(w[rnk[l]]);
		seg[id].lz = -1;
	} else {
		int mid = l + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}

void modify(int l, int r, int id, int ml, int mr, int c) {
	if (l == ml && r == mr) {
		seg[id].val.init(c);
		seg[id].lz = c;
	} else {
		int mid = l + ((r - l) >> 1);
		down(id);
		if (mr <= mid) {
			modify(l, mid, id * 2, ml, mr, c);
		} else if (ml > mid) {
			modify(mid + 1, r, id * 2 + 1, ml, mr, c);
		} else {
			modify(l, mid, id * 2, ml, mid, c);
			modify(mid + 1, r, id * 2 + 1, mid + 1, mr, c);
		}
		rise(id);
	}
}

Info query(int l, int r, int id, int ql, int qr) {
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
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

void Solution() {
	int n, q;
	cin >> n >> q;
	for (int i = 1; i <= n; ++ i) {
		cin >> w[i];
	}
	for (int i = 1; i < n; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}
	build(1);
	build(1, n, 1);

	auto Query = [&](int a, int b) {
		int ans = 0, bef1 = -1, bef2 = -1;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
				swap(bef1, bef2);
			}
			auto ret = query(1, n, 1, dfn[top[a]], dfn[a]);
			ans += ret.cnt;
			if (ret.rc_c == bef1) {
				ans --;
			}
			bef1 = ret.lc_c;
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
			swap(bef1, bef2);
		}
		auto ret = query(1, n, 1, dfn[a], dfn[b]);
		ans += ret.cnt;
		if (bef2 == ret.rc_c) {
			ans --;
		}
		if (bef1 == ret.lc_c) {
			ans --;
		}
		return ans;
	};
	auto Modify = [&](int a, int b, int c) {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			modify(1, n, 1, dfn[top[a]], dfn[a], c);
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		modify(1, n, 1, dfn[a], dfn[b], c);
	};

	while (q --) {
		char opt;
		cin >> opt;
		if (opt == 'Q') {
			int a, b;
			cin >> a >> b;
			cout << Query(a, b) << '\n';
		} else {
			int a, b, c;
			cin >> a >> b >> c;
			Modify(a, b, c);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}