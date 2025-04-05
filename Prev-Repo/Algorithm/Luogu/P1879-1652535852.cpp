#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int MOD = 1e8;
int g[13];
ll dp[13][1 << 12];
int n, m;

vector<int> state, pres[1 << 12];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		auto &now = g[i];
		for (int j = 0; j < m; ++ j) {
			int x;
			cin >> x;
			if (x == 0) {
				now += 1 << j;
			}
		}
	}
	for (int i = 0; i < 1 << m; ++ i) {
		if (!(i & i >> 1)) {
			state.push_back(i);
		}
	}
	for (auto now : state) {
		for (auto pre : state) {
			if (!(now & pre)) {
				pres[now].push_back(pre);
			}
		}
	}

	dp[0][0] = 1;
	for (int i = 1; i <= n; ++ i) {
		for (auto now : state) {
			if (!(g[i] & now)) {
				for (auto pre : pres[now]) {
					dp[i][now] += dp[i - 1][pre];
					dp[i][now] %= MOD;
				}
			}
		}
	}
	ll ans = 0;
	for (auto now : state) 
		ans = (ans + dp[n][now]) % MOD;
	cout << ans << '\n';
}