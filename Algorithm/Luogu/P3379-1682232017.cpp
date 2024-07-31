#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
	#include <debug.h>
#else
	#define debug(...)
#endif
using namespace std;
#if __cplusplus >= 202002L
	namespace rgs = std::ranges;
#endif

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using i64 = int64_t;

struct LowestCommonAncestorGraph {	
	explicit LowestCommonAncestorGraph(int _n) 
		: adj(_n), dfn(_n + 1, -1), rnk(_n + 1, -1),
	      fa(_n, -1), top(_n, -1), dep(_n, -1), son(_n, -1), siz(_n, -1) {}

	void AddDirectedEdge(int from, int to) {
		adj[from].emplace_back(to);
	}
	void AddUndirectedEdge(int u, int v) {
		AddDirectedEdge(u, v);
		AddDirectedEdge(v, u);
	}

	void Assign(int n) {
		adj.assign(n, {});
		dfn.assign(n + 1, -1);
		rnk.assign(n + 1, -1);
		fa.assign(n, -1);
		top.assign(n, -1);
		dep.assign(n, -1);
		son.assign(n, -1);
		siz.assign(n, -1);
	}

	void Init() {
		std::fill(std::begin(dep), std::end(dep), -1);
		std::fill(std::begin(fa), std::end(fa), -1);
	}

	void Build(int root) {
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
		auto dfs2 = [&, stamp{dep[root]=0}](auto &&dfs, int from, int root) mutable -> void {
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
		dfs1(dfs1, root);
		dfs2(dfs2, root, root);
	}

	int GetLowestCommonAncestor(int a, int b) {
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
	}

	auto& operator [] (int idx) {
		return adj[idx];
	}
	auto& operator [] (int idx) const {
		return adj[idx];
	}

	std::vector<std::vector<int>> adj;
	std::vector<int> dfn, rnk, fa, top, dep, son, siz;
};

void Main() {
	int n, q, root;
	cin >> n >> q >> root;
	root --;

	LowestCommonAncestorGraph adj(n);
	for (int i = 1; i <= n - 1; i ++) {
		int u, v;
		cin >> u >> v;
		u --; v --;
		adj.AddUndirectedEdge(u, v);
	}
	adj.Build(root);

	for (int _ = 1; _ <= q; _ ++) {
		int u, v;
		cin >> u >> v;
		u --; v --;
		cout << adj.GetLowestCommonAncestor(u, v) + 1 << '\n';
	}
}

std::int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);

	int32_t tot_test = 1;
	// std::cin >> tot_test;

	for (int test = 1; test <= tot_test; test += 1) {
		debug(test, "-=-=-=-");
		Main();
	}
}