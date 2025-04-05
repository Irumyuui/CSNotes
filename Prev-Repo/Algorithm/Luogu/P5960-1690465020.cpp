#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;
template <typename Type> constexpr Type inf = std::numeric_limits<Type>::max() / 2;

void Main() {
	int n, m;
	cin >> n >> m;

	std::vector adj(n + 1, std::vector<std::pair<int,i64>>{});
	for (int i = 0; i < m; i ++) {
		int u, v, w;
		cin >> u >> v >> w;
		u --; v --;
		adj[v].emplace_back(u, w);
	}

	vector<bool> inque(n);
	vector<i64> dis(n);
	vector<int> cnt(n);
	queue<int> q;
	for (int i = 0; i < n; i ++) {
		q.emplace(i);
		inque[i] = false;
	}

	bool have_loop = false;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		inque[from] = false;
		for (auto [to, ew] : adj[from]) {
			if (dis[to] > dis[from] + ew) {
				dis[to] = dis[from] + ew;
				cnt[to] = cnt[from] + 1;
				if (cnt[to] > n - 1) {
					have_loop = true;
					break;
				}
				if (!inque[to]) {
					q.emplace(to);
					inque[to] = true;
				}
			}
		}
		if (have_loop) {
			break;
		}
	}

	if (have_loop) {
		cout << "NO\n";
	} else {
		for (auto ret : dis) {
			cout << ret << ' ';
		}
		cout << '\n';
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}