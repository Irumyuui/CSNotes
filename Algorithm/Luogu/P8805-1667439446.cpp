#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

using ll = long long;

const int N = 1e5 + 10;
std::vector<int> edge[N];
ll vw[N];
void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);		
}
int fa[N], son[N], top[N], siz[N], dep[N], dfn[N], rnk[N], stamp = 0;
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
	dfs2(root,root);
}
struct Info {
	ll val;
	Info(const ll &val = 0) : val(val) {}
	friend Info operator + (const Info &a, const Info &b) {
		return Info(a.val + b.val);
	}
};
struct Node {
	Info val;
} seg[N * 4];
void rise(int id) {
	seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void build(int l, int r, int id) {
	if (l == r) {
		seg[id].val = vw[rnk[l]];
	} else {
		int mid = l  + ((r - l) >> 1);
		build(l, mid, id * 2);
		build(mid + 1, r, id * 2 + 1);
		rise(id);
	}
}
Info query(int l, int r, int id, int ql, int qr) {
	if (l == ql && r == qr) {
		return seg[id].val;
	} else {
		int mid = l + ((r - l) >> 1);
		if (qr <= mid) {
			return query(l, mid, id * 2, ql, qr);
		} else if (ql > mid) {
			return query(mid + 1, r, id * 2 + 1, ql, qr);
		} else {
			return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
		}
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, q;
	std::cin >> n >> q;
	for (int i = 1; i <= n - 1; i ++) {
		int a, b;
		std::cin >> a >> b;
		add_edge(a, b);
	}
	for (int i = 1; i <= n; i ++) {
		vw[i] = ll(edge[i].size());
		// std::cerr << vw[i] << " \n"[i == n];
	}
	build(1);
	build(1, n, 1);
	auto Query = [&](int a, int b) {
		Info ret;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				std::swap(a, b);
			}
			ret = ret + query(1, n, 1, dfn[top[a]], dfn[a]);
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			std::swap(a, b);
		}
		return ret + query(1, n, 1, dfn[a], dfn[b]);
	};
	while (q --) {
		int a, b;
		std::cin >> a >> b;
		std::cout << Query(a, b).val << '\n';
	}
}