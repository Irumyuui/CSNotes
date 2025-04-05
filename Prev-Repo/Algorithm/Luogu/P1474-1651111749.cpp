#include <bits/stdc++.h>
using namespace std;

#define int long long

int dp[10010];

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector<int> c(n);
	for (int i = 0; i < n; ++ i) {
		cin >> c[i];
	}
	dp[0] = 1;
	for (int i = 0; i < n; ++ i) {
		for (int j = c[i]; j <= m; ++ j) {
			dp[j] += dp[j - c[i]];
		}
	}
	cout << dp[m];
}