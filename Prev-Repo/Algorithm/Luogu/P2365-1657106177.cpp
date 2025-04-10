#include <bits/stdc++.h>
using namespace std;

using ll = long long;

const int N = 5010;
int t[N], f[N], s, n;
ll dp[N]; 

void Solution() {
	cin >> n >> s;
	for (int i = 1; i <= n; ++ i) {
		cin >> t[i] >> f[i];
		t[i] += t[i - 1];
		f[i] += f[i - 1];
	}
	fill(begin(dp), end(dp), numeric_limits<ll>::max());
	dp[0] = 0;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 0; j < i; ++ j) {
			dp[i] = min(
				dp[i],
				// cost[1, j] + cost[j + 1, i] + s * f[i, n]
				dp[j] + (s + t[i]) * (f[i] - f[j]) + s * (f[n] - f[i])
			);
		}
	}
	cout << dp[n];
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout.tie(nullptr);
	Solution();
}