#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 300, M = 514;
vector<int> edge[N];
void add(int from, int to) {
	edge[from].push_back(to);
}
int dfn[N], low[N], stamp = 0;
bool cut[N];
void tarjan(int from, int root) {
	dfn[from] = low[from] = ++ stamp;
	int tree_cnt = 0;
	for (auto to : edge[from]) {
		if (!dfn[to]) {
			tarjan(to, root);
			low[from] = min(low[from], low[to]);
			if (low[to] >= dfn[from]) {
				tree_cnt ++;
				if (from != root || tree_cnt >= 2) {
					cut[from] = true;
				}
			}
		} else {
			low[from] = min(low[from], dfn[to]);
		}
	}
}
int n, m;
int id[N], _id = 0, vcnt[N];
bool vis[N], vcut[N];
void dfsId(int from) {
	vis[from] = true;
	for (auto to : edge[from]) {
		if (!cut[to] && !vis[to]) {
			id[to] = id[from];
			dfsId(to);
		}
	}
}
int dfsCutCnt(int from) {
	memset(vcut, 0, sizeof vcut);
	function<int(int)> dfs = [&](int from) -> int {
		vis[from] = true;
		int cnt = 0;
		for (auto to : edge[from]) {
			if (cut[to]) {
				if (!vcut[to]) {
					cnt ++;
					vcut[to] = true;
				}
			} else if (!vis[to]) {
				cnt += dfs(to);
			}
		}
		return cnt;
	};
	return dfs(from);
}
void init() {
	fill(begin(edge), end(edge), vector<int>());
	memset(dfn, 0, sizeof dfn);
	memset(low, 0, sizeof low);
	memset(cut, 0, sizeof cut);
	memset(id, 0, sizeof id);
	memset(vis, 0, sizeof vis);
	memset(vcut, 0, sizeof vcut);
	memset(vcnt, 0, sizeof vcnt);
	stamp = 0;
	_id = 0;
	n = 0;
}
pair<int,ll> Solution() {
	for (int i = 1; i <= m; ++ i) {
		int a, b;
		cin >> a >> b;
		add(a, b);
		add(b, a);
		n = max({n, a, b});
	}
	for (int i = 1; i <= n; ++ i) {
		if (!dfn[i]) {
			tarjan(i, i);
		}
	}
	if (count(begin(cut), end(cut), true) == 0) {
		return {2, static_cast<ll>(n) * (n - 1) / 2};
	}
	for (int i = 1; i <= n; ++ i) {
		if (!cut[i] && !vis[i]) {
			id[i] = ++ _id;
			dfsId(i);
		}
	}
	for (int i = 1; i <= n; ++ i) {
		if (!cut[i]) {
			vcnt[id[i]] ++;
		}
	}
	int ans1 = 0; ll ans2 = 1;
	memset(vis, 0, sizeof vis);
	for (int i = 1; i <= n; ++ i) {
		if (!vis[i] && !cut[i]) {
			int cnt = dfsCutCnt(i);
			if (cnt == 1) {
				ans1 ++;
				ans2 *= vcnt[id[i]];
			}
		}
	}
	return {ans1, ans2};
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	for (int i = 1; cin >> m && m; ++ i) {
		init();		
		auto [ans1, ans2] = Solution();
		cout << "Case " << i << ": " << ans1 << " " << ans2 << "\n";
	}	
}