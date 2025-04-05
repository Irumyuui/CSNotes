#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 5010;
int s, n, t[N], f[N];
int dp[N];

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> s;
	for (int i = 1; i <= n; ++ i) {
		cin >> t[i] >> f[i];
	}
	for (int i = n; i >= 1; -- i) {
		t[i] += t[i + 1]; f[i] += f[i + 1];
	}
	fill(begin(dp), end(dp), numeric_limits<int>::max());
	dp[n + 1] = 0;
	for (int i = n; i >= 1; -- i) {
		for (int j = i + 1; j <= n + 1; ++ j) {
			dp[i] = min(dp[i], dp[j] + (t[i] - t[j] + s) * f[i]);
		}
	}
	cout << dp[1];
}