#include <bits/stdc++.h>
using namespace std;

const int INF = 1 << 29, N = 2e6 + 10;
int dp[N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int k, n;
	cin >> k >> n;
	fill(dp, dp + N, INF);
	dp[0] = 0;
	for (int i = 0; i < n; ++ i) {
		int c;
		cin >> c;
		for (int j = c; j < N; ++ j) {
			if (dp[j - c] + 1 <= k) {
				dp[j] = min(dp[j], dp[j - c] + 1);
			}
		}
	}
	int ans = 0;

	// for (int i = 0; i <= 20; ++ i) {
	// 	cout << i << ' ' << dp[i] << '\n';
	// }

	for (int i = 0; i < N; ++ i) {
		if (dp[i] == INF) break;
		ans = i;
	}
	cout << ans << '\n';
}