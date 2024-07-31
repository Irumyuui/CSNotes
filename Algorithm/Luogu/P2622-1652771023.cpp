#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;
int n, m;
int sw[110][10];
int dp[1 << 10];
bool vis[1 << 10];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= m; ++ i) {
		for (int j = 0; j < n; ++ j) {
			cin >> sw[i][j];
		}
	}
	fill(begin(dp), end(dp), inf);
	dp[(1 << n) - 1] = 0;
	queue<int> q;
	q.push((1 << n) - 1);
	while (!q.empty()) {
		int now = q.front();
		q.pop();
		vis[now] = false;
		for (int i = 1; i <= m; ++ i) {
			int state = now;
			for (int j = 0; j < n; ++ j) {
				auto x = sw[i][j];
				if (x == 1) {
					if (state >> j & 1)
						state ^= 1 << j;
				} else if (x == -1) {
					state |= 1 << j;
				}
			}
			if (dp[state] > dp[now] + 1) {
				dp[state] = dp[now] + 1;
				if (!vis[state])
					q.push(state), vis[state] = true;
			}
		}
	}
	auto ans = dp[0];
	if (ans == inf) cout << -1; else cout << ans;

	// cout << endl;
	// for (int i = 0; i < 1 << n; ++ i) {
	// 	cout << dp[i] << ' ';
	// }
}