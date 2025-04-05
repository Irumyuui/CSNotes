#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 7;
ll a[N][N], f[N][1 << (N - 1)];
int n, m;
vector<int> pres[1 << (N - 1)];

void solve() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= m; ++ j) {
		cin >> a[i][j];
	}
	vector<int> state;
	for (int i = 0; i < 1 << m; ++ i) {
		if (!((i & (i >> 1)) && (i & (i << 1)))) {
			state.push_back(i);
		}
	}
	fill(begin(pres), end(pres), vector<int>());
	for (auto now : state) {
		for (auto pre : state) {
			if (!(pre & now) && !((pre << 1) & now) && !((pre >> 1) & now)) {
				pres[now].push_back(pre);
			}
		}
	}
	auto getsum = [&](int x, int l) {
		ll sum = 0;
		for (int i = 1; i <= m; ++ i) {
			if (x >> (i - 1) & 1) {
				sum += a[l][i];
			}
		}
		return sum;
	};
	memset(f, 0, sizeof f);
	for (int i = 1; i <= n; ++ i) {
		for (auto now : state) {
			for (auto pre : pres[now]) {
				f[i][now] = max(f[i][now], f[i - 1][pre] + getsum(now, i));
			}
		}
	}
	ll ans = 0;
	for (auto s : state) {
		ans = max(ans, f[n][s]);
	}
	cout << ans << endl;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	for (; t --; ) {
		solve();
	}
}