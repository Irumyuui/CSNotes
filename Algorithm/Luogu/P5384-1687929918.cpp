#include <bits/stdc++.h>
using namespace std;

#if !defined (ONLINE_JUDGE)
#include "debug.hpp"
#else
#define debug(...) // なんでもいい
#endif

void Main() {
	int n, q;
	cin >> n >> q;
	vector adj(n + 1, vector<int>{});
	for (int i = 2; i <= n; i ++) {
		int x;
		cin >> x;
		adj[x].emplace_back(i);
		adj[i].emplace_back(x);
	}
	vector que(n + 1, vector<pair<int,int>>{}), que_pre(que);
	for (int i = 0; i < q; i ++) {
		int u, k;
		cin >> u >> k;
		que_pre[u].emplace_back(k, i);
	}

	debug(1);

	vector<int> dep(n + 1, -1), stk;
	vector<int> dfn(n + 1), rnk(n + 1), siz(n + 1), son(n + 1);
	stk.reserve(n);
	auto dfs1 = [&, stamp{0}](auto &&dfs, int from) mutable -> void {
		dfn[from] = ++ stamp;
		rnk[stamp] = from;
		siz[from] = 1;
		son[from] = -1;
		stk.emplace_back(from);
		for (auto [kth, id] : que_pre[from]) {
			int tag = dep[from] - kth;
			if (tag >= 0) {
				int v = stk[tag];
				que[v].emplace_back(kth, id);
			}
		}
		for (auto to : adj[from]) {
			if (dep[to] == -1) {
				dep[to] = dep[from] + 1;
				dfs(dfs, to);
				siz[from] += siz[to];
				if (son[from] == -1 || siz[to] > siz[son[from]])
					son[from] = to;
			}
		}
		stk.pop_back();
	};
	dep[1] = 0;
	dfs1(dfs1, 1);

	debug(2);

	vector<int> ret(n + 1), ans(q);
	auto dfs2 = [&, mx_dep{0}](auto &&dfs, int from, int come, bool keep) mutable -> void {
		mx_dep = max(mx_dep, dep[from]);
		for (auto to : adj[from])
			if (to != come && to != son[from])
				dfs(dfs, to, from, false);
		if (son[from] != -1) {
			dfs(dfs, son[from], from, true);
			for (auto to : adj[from]) {
				if (to != son[from] && to != come) {
					for (int i = dfn[to]; i <= dfn[to] + siz[to] - 1; i ++) {
						ret[dep[rnk[i]]] ++;
					}
				}
			}
		}
		ret[dep[from]] ++;
		for (auto [kth, qid] : que[from]) {
			auto tag = dep[from] + kth;
			ans[qid] = ret[tag] - 1;
		}
		if (!keep) {
			for (int i = dep[from]; i <= mx_dep; i ++) {
				ret[i] = 0;
			}
		}
	};
	dfs2(dfs2, 1, 0, true);

	debug(3);

	for (auto x : ans) {
		cout << x << ' ';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}