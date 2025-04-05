#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(...) std::begin(__VA_ARGS__), std::end(__VA_ARGS__)
using ll = long long;

const int N = 1e3 + 10;
ll a[N], s[N];
ll limit, ans = 0;

void dfs(int id, ll w) {
	if (s[id] + w <= limit) {
		ans = max(ans, s[id] + w);
		return;
	}
	ans = max(ans, w);
	if (id == 0) {
		return;
	}
	if (a[id] + w <= limit) {
		dfs(id - 1, w + a[id]);
	}
	dfs(id - 1, w);
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n >> limit;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		s[i] += a[i] + s[i - 1];
	}
	dfs(n, 0);
	cout << ans << endl;
}