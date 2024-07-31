#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	cin >> n >> m;
	vector a(n + 1, vector<int>(m + 1));
	vector f(n + 1, vector(m + 1, a));
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			cin >> a[i][j];
		}
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= m; ++ j) {
			for (int k = 1; k <= n; ++ k) {
				for (int l = 1; l <= m; ++ l) {
					f[i][j][k][l] = max({
						f[i - 1][j][k - 1][l],
						f[i - 1][j][k][l - 1],
						f[i][j - 1][k - 1][l],
						f[i][j - 1][k][l - 1]
					}) + (i == k && j == l ? a[i][j] : a[i][j] + a[k][l]);
				}
			}
		}
	}
	cout << f[n][m][n][m] << '\n';
}