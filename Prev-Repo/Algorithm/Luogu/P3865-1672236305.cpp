#include <bits/stdc++.h>
using namespace std;

auto main() -> int {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector f(__lg(n + 1) + 1, vector<int>(n + 1));
	for (int i = 1; i <= n; i ++) {
		cin >> f[0][i];
	}
	for (int i = 1; i <= __lg(n); i ++) {
		for (int j = 1; j + (1 << i) - 1 <= n; j ++) {
			f[i][j] = max(f[i - 1][j], f[i - 1][j + (1 << (i - 1))]);
		}
	}
	auto query = [&](int l, int r) {
		int s = __lg(r - l + 1);
		return max(f[s][l], f[s][r - (1 << s) + 1]);
	};
	while (m --) {
		int l, r;
		cin >> l >> r;
		cout << query(l, r) << '\n';
	}
}