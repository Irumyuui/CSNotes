#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define all(...) std::begin(__VA_ARGS__), std::end(__VA_ARGS__)
using ll = long long;

const int N = 5;
int n;
ll a[N][N], c[N * N];
ll sum, tag;
bool vis[N * N];

bool dfs (int x, int y) {

	if (x > n) {
		ll tmp = 0;
		for (int i = 1; i <= n; ++ i) {
			tmp += a[y][i];
		}
		if (tmp != tag) {
			return false;
		} else {
			y ++;
			x = 1;
		}
	}
	if (y > n) {
		for (int i = 1; i <= n; ++ i) {
			ll temp = 0;
			for (int j = 1; j <= n; ++ j) {
				temp += a[j][i];
			}
			if (temp != tag) {
				return false;
			}
		}
		ll tmp = 0;
		for (int i = 1; i <= n; ++ i) {
			tmp += a[i][i];
		}
		if (tmp != tag) {
			return false;
		}
		tmp = 0;
		for (int i = 1; i <= n; ++ i) {
			tmp += a[i][n - i + 1];
		}
		return tmp == tag;
	}
	for (int i = 1; i <= n * n; ++ i) {
		if (!vis[i]) {
			vis[i] = true;
			a[y][x] = c[i];
			if (dfs(x + 1, y)) {
				return true;
			}
			vis[i] = false;
			a[y][x] = 0;
		}
	}
	return false;
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	cin >> n;
	for (int i = 1; i <= n * n; ++ i) {
		cin >> c[i];
		sum += c[i];
	}
	sort(c + 1, c + 1 + n * n);
	tag = sum / n;
	dfs(1, 1);
	cout << tag << endl;
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j <= n; ++ j) {
			cout << a[i][j] << " \n"[j == n];
		}
	}
}