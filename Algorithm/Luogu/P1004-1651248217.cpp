#include <bits/stdc++.h>
using namespace std;

const int N = 10;
int c[N][N], dp[N][N][N][N];

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n;
	cin >> n;
	{
		int a, b, d;
		while (cin >> a >> b >> d && (a || b || d)) {
			c[a][b] = d;
		}
	}
	for (int i = 1; i <= n; ++ i) 
		for (int j = 1; j <= n; ++ j)
			for (int k = 1; k <= n; ++ k)
				for (int l = 1; l <= n; ++ l) {
					auto w = i == k && j == l ? c[i][j] : c[i][j] + c[k][l];
					dp[i][j][k][l] = max({
						dp[i - 1][j][k - 1][l], dp[i - 1][j][k][l - 1],
						dp[i][j - 1][k - 1][l], dp[i][j - 1][k][l - 1]
					}) + w;
				}
	cout << dp[n][n][n][n] << '\n';
}