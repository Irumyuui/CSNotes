#include <bits/stdc++.h>
using namespace std;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	vector d(n + 2, vector<int>(n + 2));
	while (m --> 0) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		d[x1][y1] ++;
		d[x2 + 1][y1] --;
		d[x1][y2 + 1] --;
		d[x2 + 1][y2 + 1] ++;
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			d[i][j] += d[i - 1][j];
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			d[i][j] += d[i][j - 1];
		}
	}
	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++) {
			cout << d[i][j] << " \n"[j == n];
		}
	}
}