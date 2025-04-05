/* 聚会 */
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

const int N = 5e5 + 10;
vector<int> edge[N];

void add_edge(int from, int to) {
	edge[from].push_back(to);
	edge[to].push_back(from);
}

int dep[N], siz[N], son[N], top[N], dfn[N], fa[N];
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
	if (son[from] == -1) {
		return;
	}
	dfs2(son[from], root);
	for (auto to : edge[from]) {
		if (to != fa[from] && to != son[from]) {
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

void Solution() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n - 1; ++ i) {
		int a, b;
		cin >> a >> b;
		add_edge(a, b);
	}	
	build(1);

	auto lca = [&](int a, int b) {
		int ret = 0;
		while (top[a] != top[b]) {
			if (dep[top[a]] < dep[top[b]]) {
				swap(a, b);
			}
			ret += dfn[a] - dfn[top[a]] + 1;
			a = fa[top[a]];
		}
		if (dep[a] > dep[b]) {
			swap(a, b);
		}
		ret += dfn[b] - dfn[a];
		return pair{a, ret};
	};

	while (m --) {
		int a, b, c;
		cin >> a >> b >> c;
		vector<int> tmp(3);
		tmp[0] = lca(a, b).first, tmp[1] = lca(a, c).first, tmp[2] = lca(b, c).first; 
		sort(begin(tmp), end(tmp), [&](const int &a, const int &b) {
			return dep[a] > dep[b];
		});
		int tag = tmp.front();
		int ans = lca(a, tag).second + lca(b, tag).second + lca(c, tag).second;
		cout << tag << ' ' << ans << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}