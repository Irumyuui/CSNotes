/* P1462 通往奥格瑞玛的道路 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

void Solution() {
	int n, m, blood;
	cin >> n >> m >> blood;

	vector<vector<array<int,2>>> g(n);
	vector<int> cost(n);
	for (int i = 0; i < n; ++ i) {
		cin >> cost[i];
	}
	for (int i = 1; i <= m; ++ i) {
		int from, to, w;
		cin >> from >> to >> w;
		from --;
		to --;
		g[from].push_back({to, w});
		g[to].push_back({from, w});
	}
	
	vector<int> dis(n);
	vector<bool> vis(n);
	auto spfa = [&](int s, int can) {
		fill(begin(dis), end(dis), inf<int>);
		queue<int> q;
		q.push(s);
		dis[s] = 0;
		while (!q.empty()) {
			int from = q.front();
			q.pop();
			vis[from] = false;
			for (auto [to, w] : g[from]) {
				if (cost[to] > can) {
					continue;
				}
				if (dis[to] > dis[from] + w) {
					dis[to] = dis[from] + w;
					if (!vis[to]) {
						vis[to] = true;
						q.push(to);
					}
				}
			}
		}		
		return dis[n - 1] <= blood;
	};

	int L = 0, R = inf<int>;
	for (int i = 1; i <= 100; ++ i) {
		int mid = L + ((R - L) >> 1);
		debug(L, R, mid);
		if (spfa(0, mid)) {
			R = mid;
		} else {
			L = mid + 1;
		}
	}
	if (R == inf<int>) {
		cout << "AFK";
	} else {
		cout << L;
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}