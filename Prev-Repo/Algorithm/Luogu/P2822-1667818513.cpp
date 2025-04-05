#include <bits/stdc++.h>

const int N = 2e3 + 10;
int c[N][N], s[N][N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t, k;
	std::cin >> t >> k;
	memset(c, -1, sizeof(c));
	for (int i = 1; i < N; i ++) {
		c[i][0] = c[i][i] = 1 % k;
		for (int j = 1; j < i; j ++) {
			c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % k;
		}
	}
	for (int i = 1; i < N; i ++) {
		for (int j = 1; j < N; j ++) {
			s[i][j] = s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1] + (c[i][j] == 0);
		}
	}
	while (t --) {
		int n, m;
		std::cin >> n >> m;
		std::cout << s[n][m] << '\n';
	}
}