#include <bits/stdc++.h>
using namespace std;

struct Info {
	int val;
	Info(int val = {}) : val{val} {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info {
			max(a.val, b.val)
		};
	}
};
struct Node {
	Info val;
	int lc, rc;
	Node(const Info &val = {}, int lc = {}, int rc = {}) : val{val}, lc{lc}, rc{rc} {}
};
vector<Node> seg{{}};

int GetNode() {
	seg.emplace_back(0, 0, 0);
	return int(seg.size()) - 1;
}
void extends(int now, int pre) {
	seg[now] = seg[pre];
}
void Rise(int id) {
	seg[id].val = seg[seg[id].lc].val + seg[seg[id].rc].val;
}

void Opt(int l, int r, int &now, int tag, int d) {
	if (!now) {
		now = GetNode();
	}
	if (l == r) {
		seg[now].val.val += d;		
	} else {
		int mid = l + ((r - l) >> 1);
		if (tag <= mid) {
			Opt(l, mid, seg[now].lc, tag, d);
		} else {
			Opt(mid + 1, r, seg[now].rc, tag, d);
		}
		Rise(now);
	}
}

pair<int,int> Query(int l, int r, int id) {
	if (!id) {
		return {0, -1};
	}
	if (l == r) {
		return {l, seg[id].val.val};
	} else {
		int mid = l + ((r - l) >> 1);
		if (seg[seg[id].lc].val.val == seg[id].val.val) {
			return Query(l, mid, seg[id].lc);
		} else {
			return Query(mid + 1, r, seg[id].rc);
		}
	}
}

// Merge Tree b into Tree a
void Merge(int &a, int &b, int l, int r) {
	if (!a) {
		a = b;
	} else if (!b) {
		return;
	} else {
		if (l == r) {
			seg[a].val.val += seg[b].val.val;
		} else {
			int mid = l + ((r - l) >> 1);
			Merge(seg[a].lc, seg[b].lc, l, mid);
			Merge(seg[a].rc, seg[b].rc, mid + 1, r);
			Rise(a);
		}
	}
}

void Main() {
	int n, q;
	cin >> n >> q;
	
	vector adj(n + 1, vector<int>());
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	vector<int> dep(n + 1, -1), dfn(n + 1), rnk(n + 1), siz(n + 1), son(n + 1), fa(n + 1, -1), top(n + 1);
	[&](int root) {
		auto dfs1 = [&](auto &&dfs, int from) -> void {
			son[from] = -1;
			siz[from] = 1;
			for (auto to : adj[from]) {
				if (dep[to] == -1) {
					dep[to] = dep[from] + 1;
					fa[to] = from;
					dfs(dfs, to);
					siz[from] += siz[to];
					if (son[from] == -1 || siz[to] > siz[son[from]]) {
						son[from] = to;
					}
				}
			}
		};
		auto dfs2 = [&, stamp{0}](auto &&dfs, int from, int root) mutable -> void {
			top[from] = root;
			dfn[from] = ++ stamp;
			rnk[stamp] = from;
			if (son[from] == -1) {
				return;
			}
			dfs(dfs, son[from], root);
			for (auto to : adj[from]) {
				if (to != son[from] && to != fa[from]) {
					dfs(dfs, to, to);
				}
			}
		};
		dep[root] = 0;
		dfs1(dfs1, root);
		dfs2(dfs2, root, root);
	}(1);

	auto GetLCA = [&](int a, int b) -> int {
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			a = fa[top[a]];
		} 
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		return a;
	};

	constexpr int L = 1, R = int(1e5);

	seg.reserve(int(2e7 + 10));
	vector<int> root(n + 1);
	for (int _ = 1; _ <= q; _ ++) {
		int x, y, z;
		cin >> x >> y >> z;

		int lca = GetLCA(x, y);
		Opt(L, R, root[x], z, 1);		
		Opt(L, R, root[y], z, 1);		
		Opt(L, R, root[lca], z, -1);

		if (fa[lca] != -1) {
			Opt(L, R, root[fa[lca]], z, -1);
		}
	}

	vector<int> ans(n + 1);
	auto dfs = [&](auto &&dfs, int from) -> void {
		for (auto to : adj[from]) {
			if (dep[to] == dep[from] + 1) {
				dfs(dfs, to);
				Merge(root[from], root[to], L, R);
			}
		}
		auto ret = Query(L, R, root[from]);
		if (ret.second <= 0) {
			ans[from] = 0;
		} else {
			ans[from] = ret.first;
		}
	};
	dfs(dfs, 1);

	for (auto &x : ans | views::drop(1)) {
		cout << x << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}