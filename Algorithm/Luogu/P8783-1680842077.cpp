#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int n, m;
	i64 k;
	cin >> n >> m >> k;

	vector a(n + 1, vector<i64>(m + 1));
	for (auto &v : a | views::drop(1))
		for (auto &x : v | views::drop(1))
			cin >> x;
	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];

	auto Get = [&](int x1, int y1, int x2, int y2) {
		return a[x2][y2] - a[x1 - 1][y2] - a[x2][y1 - 1] + a[x1 - 1][y1 - 1];
	};

	i64 ans = 0;
	for (int up = 1; up <= n; up ++) 
		for (int down = up; down <= n; down ++) 
			for (int l = 1, r = 1; r <= m; r ++) {
				while (l <= r && Get(up, l, down, r) > k)
					l ++;
				ans += max<i64>(0, r - l + 1);
			}
	cout << ans << '\n';
}