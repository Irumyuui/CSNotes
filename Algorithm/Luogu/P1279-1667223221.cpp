#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	string a, b; int k;
	cin >> a >> b >> k;
	int n = a.size(), m = b.size();
	a = ' ' + a;
	b = ' ' + b;
	vector f(n + 1, vector<int>(m + 1, -1));
	auto dfs = [&](auto &&dfs, int i, int j) {
		if (f[i][j] != -1) {
			return f[i][j];
		}
		if (i == 0) {
			return f[i][j] = j * k;
		}
		if (j == 0) {
			return f[i][j] = i * k;
		}
		int ret = min({
			dfs(dfs, i - 1, j) + k,
			dfs(dfs, i, j - 1) + k,
			dfs(dfs, i - 1, j - 1) + std::abs(a[i] - b[j]) 
		});
		return f[i][j] = ret;
	};
	cout << dfs(dfs, n, m) << '\n';
}