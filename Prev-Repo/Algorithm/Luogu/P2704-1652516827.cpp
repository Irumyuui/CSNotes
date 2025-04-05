#include <bits/stdc++.h>
using namespace std;

const int N = 100, M = 10;

int g[N + 10];
int dp[2][1 << M][1 << M];
int cnt[1 << M];
vector<int> trans, pres[1 << M];
bool check(int i) {
	return !(i & i >> 1 || i & i >> 2);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		auto &now = g[i];
		for (int j = 0; j < m; ++ j) {
			char x;
			cin >> x;
			if (x == 'H') now += (1 << j);
		}
	}
	for (int i = 0; i < (1 << m); ++ i) {
		if (check(i)) {
			trans.push_back(i);
			for (int j = 0; j < m; ++ j) {
				cnt[i] += (i >> j) & 1;
			}
		}
	}
	for (auto now : trans) {
		for (auto pre : trans) {
			if (!(now & pre)) {
				pres[now].push_back(pre);
			}
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (auto now : trans) {
			if (!(now & g[i])) {
				for (auto pre1 : pres[now]) {
					for (auto pre2 : pres[pre1]) {
						if (!(now & pre2)) {
							dp[i & 1][now][pre1] = max(
									dp[i & 1][now][pre1], dp[(i - 1) & 1][pre1][pre2] + cnt[now]
								);
						}
					}
				}
			}
		}
	}
	int ans = 0;
	for (auto now : trans) {
		for (auto pre : trans) {
			ans = max(ans, dp[n & 1][now][pre]);
		}
	}
	cout << ans << '\n';
}