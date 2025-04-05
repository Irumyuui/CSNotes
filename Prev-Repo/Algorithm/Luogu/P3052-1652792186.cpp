#include <bits/stdc++.h>

using namespace std;

const int inf = 1 << 30;
int dp[1 << 18], space[1 << 18];
int use[18];
int n, m;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n >> m;
	for (int i = 0; i < n; ++ i) {
		cin >> use[i];
	}
	fill(begin(dp), end(dp), inf);
	dp[0] = 1, space[0] = m;
	for (int i = 0; i < 1 << n; ++ i) {
		int prestate = i;
		for (int j = 0; j < n; ++ j) {
			if (prestate >> j & 1) {
				continue;
			}
			int nowstate = prestate | (1 << j);
			auto &nowles = space[nowstate], &preles = space[prestate], &need = use[j];
			if (preles >= need) {
				dp[nowstate] = min(dp[nowstate], dp[prestate]);
				nowles = max(nowles, preles - need);
			} else {
				dp[nowstate] = min(dp[nowstate], dp[prestate] + 1);
				nowles = max(nowles, m - need);
			}
		}
	}
	cout << dp[(1 << n) - 1];
}