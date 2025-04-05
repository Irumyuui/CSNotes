#include <bits/stdc++.h>
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using namespace std;
using ll = long long;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<vector<int>> g(n);
	for (int i = 0; i < m; ++ i) {
		int a, b;
		cin >> a >> b;
		a --; b --;
		g[a].emplace_back(b);
		g[b].emplace_back(a);
	}
	vector<int> dfn(n, inf<int>), low(n, inf<int>), siz(n, 0);
	vector<ll> ans(n, 0);
	vector<bool> iscut(n, false);
	int stamp = 0;
	function<void(int,bool)> dfs = [&](int from, bool isroot) {
		dfn[from] = low[from] = ++ stamp;
		int tree_cnt = 0;
		ll tmp = 0;
		siz[from] = 1;
		for (auto to : g[from]) {
			if (dfn[to] == inf<int>) {
				dfs(to, false);
				low[from] = min(low[from], low[to]);
				siz[from] += siz[to];
				if (low[to] >= dfn[from]) {
					tree_cnt ++;
					if (!isroot || tree_cnt >= 2) {
						iscut[from] = true;
					}
					ans[from] += tmp * siz[to];
					tmp += siz[to];
				}
			} else {
				low[from] = min(low[from], dfn[to]);
			}
		}
		ans[from] += tmp * (n - tmp - 1);
	};
	dfs(0, true);
	for (int i = 0; i < n; ++ i) {
		if (iscut[i]) {
			cout << (ans[i] + n - 1) * 2 << '\n';
		} else {
			cout << 2 * (n - 1) << '\n';
		}
	}
}