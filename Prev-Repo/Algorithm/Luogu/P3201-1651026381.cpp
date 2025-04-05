#include <bits/stdc++.h>
using namespace std;

const int N = 2e6 + 10;
vector<int> colc[N];
int id[N], col[N], ans = 0;

void solve(int x, int y) {
	for (auto i : colc[x]) {
		if (col[i - 1] == y) {
			ans --;
		}
		if (col[i + 1] == y) {
			ans --;
		}
	}
	for (auto i : colc[x]) {
		col[i] = y;
		colc[y].push_back(i);
	}
	colc[x].clear();
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> col[i];
		if (col[i - 1] != col[i]) {
			ans ++;
		}
		id[col[i]] = i;
		colc[col[i]].push_back(i);
	}
	for (int i = 1; i <= m; ++ i) {
		int opt; cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			if (x == y) continue;
			if (colc[x].size() > colc[y].size()) {
				swap(id[x], id[y]);
			}
			solve(x, y);
		} else {
			cout << ans << '\n';
		}
	}
}