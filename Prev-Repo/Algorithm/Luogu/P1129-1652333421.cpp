#include <bits/stdc++.h>
using namespace std;

const int N = 210;
int n, g[N][N], cat[N];
bool vis[N];

bool match(int i) {
	for (int j = 1; j <= n; ++ j) {
		if (g[i][j] && !vis[j]) {
			vis[j] = true;
			if (cat[j] == 0 || match(cat[j])) {
				cat[j] = i;
				return true;
			}
		}
	}
	return false;
}
int xiong() {
	int cnt = 0;
	memset(cat, 0, sizeof cat);
	for (int i = 1; i <= n; ++ i) {
		memset(vis, 0, sizeof vis);
		if (match(i)) cnt ++;
	}
	return cnt;
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int T;
	cin >> T;
	for (; T --; ) {
		cin >> n;
		for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j) {
			cin >> g[i][j];
		}
		auto ans = xiong();
		if (ans == n) {
			cout << "Yes";
		} else {
			cout << "No";
		}
		cout << '\n';
	}
}