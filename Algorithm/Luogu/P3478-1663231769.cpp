#include <bits/stdc++.h>

#define all(x) std::begin(x), std::end(x)
#define int long long

using namespace std;

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<vector<int>> g(n);
	for (int i = 0; i < n - 1; i ++) {
		int a, b;
		cin >> a >> b;
		a --; b --;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	vector<bool> vis(n);
	vector<int> siz(n), f(n), ff(n);
	function<void(int)> down = [&](int from) {
		siz[from] = 1;
		vis[from] = true;
		for (int to : g[from]) {
			if (!vis[to]) {
				down(to);
				siz[from] += siz[to];
				f[from] += f[to] + siz[to];
			}
		}
	};
	function<void(int)> rise = [&](int from) {
		vis[from] = true;
		for (int to : g[from]) {
			if (!vis[to]) {
				ff[to] = ff[from] + (n - siz[to])  // 根节点另一边
					+ (f[from] - f[to] - siz[to]);  // 另一边子树
				rise(to);
			}
		}
	};	
	down(0);
	fill(all(vis), false);
	rise(0);
	int ans = 0, id = 0;
	for (int i = 0; i < n; ++ i) {
		if (f[i] + ff[i] > ans) {
			ans = f[i] + ff[i];
			id = i + 1;
		}
	}
	cout << id << '\n';
}