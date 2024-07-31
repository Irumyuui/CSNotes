/* File: P2850 [USACO06DEC]Wormholes G */
#include <bits/stdc++.h>
using namespace std;

template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;

void Solution() {
	int n, m, k;
	cin >> n >> m >> k;
	vector<vector<pair<int,int>>> edge(n);
	for (int i = 1; i <= m; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		from --; to --;
		edge[from].push_back({to, w});
		edge[to].push_back({from, w});
	}
	for (int i = 1; i <= k; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		from --; to --;
		edge[from].push_back({to, -w});
	}
	
	auto spfa = [&]() {
		vector<int> cnt(n), dis(n);
		vector<bool> vis(n);
		queue<int> q;
		for (int i = 0; i < n; ++ i) {
			q.push(i);
			vis[i] = true;
		}
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			vis[from] = false;
			for (auto [to, w] : edge[from]) {
				if (dis[to] > dis[from] + w) {
					dis[to] = dis[from] + w;
					cnt[to] = cnt[from] + 1;
					if (cnt[to] >= n) {
						return false;
					}
					if (!vis[to]) {
						q.push(to);
						vis[to] = true;
					}
				}
			}
		}
		return true;
	};

	if (!spfa()) {
		cout << "YES\n";
	} else {
		cout << "NO\n";
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		Solution();
	}
}