#include <bits/stdc++.h>
using namespace std;

int live[55], goback[55], a[55][55];
int n;

int cat[55];
bool vis[55];
bool match(int i) {
	for (int j = 1; j <= n; ++ j) 
		if (a[i][j] && live[j] && !vis[j]) {
			vis[j] = true;
			if (cat[j] == 0 || match(cat[j])) {
				cat[j] = i;
				return true;
			}
		}
	return false;
}
bool xiong() {
	memset(cat, 0, sizeof cat);
	for (int i = 1; i <= n; ++ i) {
		if (live[i] == 0 || (live[i] == 1 && !goback[i])) {
			memset(vis, 0, sizeof vis);
			if (!match(i))
				return false;
		}
	}
	return true;
}

void solve() {
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		cin >> live[i];
	}
	for (int i = 1; i <= n; ++ i) {
		cin >> goback[i];
	}
	for (int i = 1; i <= n; ++ i) for (int j = 1; j <= n; ++ j)
		cin >> a[i][j];
	for (int i = 1; i <= n; ++ i) a[i][i] = 1;
	if (xiong()) {
		cout << "^_^\n";
	} else {
		cout << "T_T\n";
	}
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	for (; t --; ) {
		solve();
	}
}