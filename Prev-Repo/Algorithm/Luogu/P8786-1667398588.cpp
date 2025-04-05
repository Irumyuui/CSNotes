#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int N = 210, MOD = 1e9 + 7;
ll f[N][N][N];

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	memset(f, -1, sizeof(f));
	int n, m;
	cin >> n >> m;
	// n 店 m 花 zun Zun
	auto dfs = [&](auto &&dfs, int n, int m, int zun) -> ll {
		if (n == 0 && m == 0) {
			return zun == 0;
		}
		if (n < 0 || m < 0 || zun > 100 || (n && m <= 0)) {
			return 0;
		}
		if (~f[n][m][zun]) {
			return f[n][m][zun];
		}
		ll ret = 0;
		if (zun) {
			ret = ( dfs(dfs, n - 1, m, zun * 2) + dfs(dfs, n, m - 1, zun - 1) ) % MOD;
		} else {
			ret = dfs(dfs, n - 1, m, zun * 2) % MOD;
		}
		return f[n][m][zun] = ret;
	};
	cout << dfs(dfs, n, m, 2) << '\n';
}