#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	vector<int> c(n + 1, 0);
	for (int i = 1; i <= n; ++ i) {
		cin >> c[i];
	}
	vector<array<int, 2>> dp(n + 1, {1, 0});
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < i; ++ j) {
			if (c[j] < c[i]) {
				dp[i][0] = max(dp[i][0], dp[j][1] + 1);
			}
			if (c[j] > c[i]) {
				dp[i][1] = max(dp[i][1], dp[j][0] + 1);
			}
		}
	}
	int ans = 0;
	for (int i = 1; i <= n; ++ i) {
		ans = max({
			ans, dp[i][0], dp[i][1]
		});
	}
	cout << ans << '\n';
}