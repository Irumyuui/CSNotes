#include <bits/stdc++.h>

using namespace std;

const int N = 1e6 + 10;

struct LcaGraph {
	vector<int> edge[N];
	void add_edge(int from, int to) {
		edge[from].push_back(to);
		edge[to].push_back(from);
	}
	int siz[N], top[N], son[N], fa[N], dep[N];
	void dfs1(int from) {
		son[from] = -1;
		siz[from] = 1;
		for (auto to : edge[from]) {
			if (!dep[to]) {
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
	void build(int sta) {
		dep[sta] = 1;
		dfs1(sta);
		dfs2(sta, sta);
	}
	int lca(int a, int b) {
		while (top[a] != top[b]) {
			if (dep[top[a]] > dep[top[b]]) {
				a = fa[top[a]];
			} else {
				b = fa[top[b]];
			}
		}
		if (dep[a] < dep[b]) {
			return a;
		} else {
			return b;
		}
	}
} tree;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m, root;
	cin >> n >> m >> root;
	root --;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		a --;
		b --;
		tree.add_edge(a, b);
	}
	tree.build(root);
	for (int i = 0; i < m; ++ i) {
		int a, b;
		cin >> a >> b;
		a --; b --;
		cout << tree.lca(a, b) + 1 << '\n';
	}
}