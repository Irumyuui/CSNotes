#include <bits/stdc++.h>
using namespace std;

void Main() {
	int n, q;
	cin >> n >> q;

	vector<int> vw(n + 1);
	for (auto &x : vw | views::drop(1)) {
		char t;
		cin >> t;
		x = 1 << (t == 'H');
	}

	vector adj(n + 1, vector<int>{});
	for (int i = 1; i < n; i ++) {
		int u, v;
		cin >> u >> v;
		adj[u].emplace_back(v);
		adj[v].emplace_back(u);
	}

	vector<int> dfn(n + 1), rnk(n + 1), siz(n + 1), son(n + 1), fa(n + 1), top(n + 1), dep(n + 1, -1);
	[&](int root) {
		auto dfs1 = [&](auto &&dfs, int from) -> void {
			siz[from] = 1;
			son[from] = -1;
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
			for (auto to : adj[from])
				if (to != fa[from] && to != son[from]) {
					dfs(dfs, to, to);
				}
		};
		dep[root] = 0;
		dfs1(dfs1, root);
		dfs2(dfs2, root, root);
	} (1);

	struct Info {
		int val;
		Info operator + (const Info &a) {
			return {val | a.val};
		}
	};
	struct Node {
		Info val;
	};
	vector<Node> seg(n * 4 + 10);
	auto build = [&](auto &&dfs, int l, int r, int id) -> void {
		if (l == r) {
			seg[id].val.val = vw[rnk[l]];
		} else {
			int mid = l + ((r - l) >> 1);
			dfs(dfs, l, mid, id * 2);
			dfs(dfs, mid + 1, r, id * 2 + 1);
			seg[id].val  = seg[id * 2].val + seg[id * 2 + 1].val;
		}
	};
	build(build, 1, n, 1);

	auto query = [&](auto &&dfs, int l, int r, int id, int ql, int qr) -> Info {
		if (l == ql && r == qr) {
			return seg[id].val;
		} else {
			int mid = l + ((r - l) >> 1);
			if (qr <= mid) {
				return dfs(dfs, l, mid, id * 2, ql, qr);
			} else if (ql > mid) {
				return dfs(dfs, mid + 1, r, id * 2 + 1, ql, qr);
			} else {
				return dfs(dfs, l, mid, id * 2, ql, mid) + dfs(dfs, mid + 1, r, id * 2 + 1, mid + 1, qr);
			}
		}
	};

	for (int i = 1; i <= q; i ++) {
		int a, b;
		cin >> a >> b;

		Info ret = {0};
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			ret = ret + query(query, 1, n, 1, dfn[top[a]], dfn[a]);
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		ret = ret + query(query, 1, n, 1, dfn[a], dfn[b]);
		
		char x;
		cin >> x;
		if ((ret.val & (1 << (x == 'H')))) {
			cout << 1;
		} else {
			cout << 0;
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}