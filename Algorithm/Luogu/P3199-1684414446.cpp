#include <bits/stdc++.h>
using namespace std;

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

template <typename T, typename Compare = std::greater<T>, template <typename E, typename Alloc = std::allocator<E>> typename Container = std::vector>
using PriorityQueue = std::priority_queue<T, Container<T>, Compare>;

using i64 = int64_t;
using db = double;

void Main() {
	int n, m;
	cin >> n >> m;

	db l = inf<int>, r = -inf<int>, ans = -inf<int>;
	vector adj(n + 1, vector<pair<int,db>>{});
	for (int i = 1; i <= m; i ++) {
		int u, v;
		db w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		l = min(l, w);
		r = max(r, w);
	}

	vector<db> dis(n + 1);
	vector<int> cnt(n + 1);
	vector<bool> vis(n + 1);
	auto check = [&](db mid) -> bool {
		PriorityQueue<pair<db,int>> q;
		for (int i = 1; i <= n; i ++) {
			dis[i] = cnt[i] = 0;
			q.emplace(dis[i], i);
			vis[i] = true;
		}

		while (!q.empty()) {
			int from = q.top().second;
			q.pop();
			vis[from] = false;
			for (auto [to, w] : adj[from]) {
				if (dis[to] > dis[from] + w - mid) {
					dis[to] = dis[from] + w - mid;
					cnt[to] = cnt[from] + 1;
					if (cnt[to] > n - 1) {
						return true;
					}
					if (!vis[to]) {
						vis[to] = true;
						q.emplace(dis[to], to);
					}
				}
			}
		}

		return false;
	};

	while (r - l >= 1e-9) {
		auto mid = l + ((r - l) / 2);
		if (check(mid)) {
			ans = mid;
			r = mid;
		} else {
			l = mid;
		}	
	}

	cout << ans << '\n'; 
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(8);

	Main();
}