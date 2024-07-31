#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int,int>>> g(n);
	for (int i = 0; i < m; ++ i) {
		int a, b, c;
		cin >> a >> b >> c;
		a --; b --;
		g[a].emplace_back(b, c);
		g[b].emplace_back(a, c);
	}
	vector<int> col(n);
	function<bool(int,int,int)> dfs = [&](int from, int c, int low) -> bool {
		col[from] = c;
		for (auto [to, w] : g[from]) {
			if (w <= low) continue;
			if (!col[to]) {
				if (!dfs(to, -c, low))
					return false;
			} else if (col[to] == col[from]) {
				return false;
			}
		}
		return true;
	};
	auto check = [&](int low) {
		fill(begin(col), end(col), 0);
		for (int i = 0; i < n; ++ i) {
			if (!col[i]) 
				if (!dfs(i, 1, low))
					return false;
		}
		return true;
	};
	int l = 0, r = 1e9, ans = -1;
	while (l <= r) {
		int mid = l + ((r - l) >> 1);
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else {
			l = mid + 1;
		}
	}
	cout << ans << '\n';
}