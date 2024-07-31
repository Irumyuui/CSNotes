#include <bits/stdc++.h>

template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
const int N = 1e4 + 10;
std::vector<std::pair<int,int>> edge[N];
int dis[N];
bool vis[N];
void add_edge(int from, int to, int w) {
	edge[from].emplace_back(to, w);
	edge[to].emplace_back(from, w);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m, k;
	std::cin >> n >> m >> k;
	for (int i = 1; i <= m; i ++) {
		int a, b, w;
		std::cin >> a >> b >> w;
		add_edge(a, b, w);
	}
	auto check = [&](int low) -> bool {
		std::fill(std::begin(dis), std::end(dis), inf<int>);
		std::fill(std::begin(vis), std::end(vis), false);
		std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> q;
		q.emplace(dis[1] = 0, 1);
		while (!q.empty()) {
			int from = q.top().second;
			q.pop();
			if (vis[from]) continue;
			vis[from] = true;
			for (auto [to, w] : edge[from]) {
				int ww = w > low;
				if (!vis[to] && dis[to] > dis[from] + ww) {
					dis[to] = dis[from] + ww;
					q.emplace(dis[to], to);
				}
			}
		}
		return dis[n] <= k;
	};
	int l = 0, r = inf<int>, ans = -1;;
	while (l <= r) {
		int mid = l + ((r - l) >> 1);
		if (check(mid)) {
			r = mid - 1;
			ans = mid;
		} else {
			l = mid + 1;
		}
	}
	std::cout << ans << '\n';
}