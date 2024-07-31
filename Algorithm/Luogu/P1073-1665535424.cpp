#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
std::mt19937 mrand(std::chrono::system_clock::now().time_since_epoch().count());
using ll = int64_t;
using ld = long double;

const int N = 100005 * 3;
vector<pair<int,int>> edge[N];
int dis[N];
bool vis[N];
void add_edge(int from, int to, int w) {
	edge[from].emplace_back(to, w);
}

void spfa(int s) {
	fill(begin(dis), end(dis), -inf<int>);
	queue<int> q;
	q.push(s);
	dis[s] = 0;
	while (!q.empty()) {
		int from = q.front();
		q.pop();
		vis[from] = false;
		for (auto [to, w] : edge[from]) {
			if (dis[to] < dis[from] + w) {
				dis[to] = dis[from] + w;
				if (!vis[to]) {
					vis[to] = true;
					q.push(to);
				}
			}
		}
	}
}

void Solution() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i ++) {
		int x;
		cin >> x;
		add_edge(i, i + n, -x);
		add_edge(i + n, i + n * 2, x);
	}
	for (int i = 0; i < m; i ++) {
		int a, b, z;
		cin >> a >> b >> z;
		add_edge(a, b, 0);
		add_edge(a + n, b + n, 0);
		add_edge(a + n * 2, b + n * 2, 0);
		if (z == 2) {
			add_edge(b, a, 0);
			add_edge(b + n, a + n, 0);
			add_edge(b + n * 2, a + n * 2, 0);
		}
	}
	spfa(1);
	cout << dis[n * 3];
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}