#include <bits/stdc++.h>
using namespace std;

vector<int> colc[1000001];
int id[1000001], col[100001], ans = 0;

void modify(int x, int y) {
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
		// id[col[i]] = i;
		id[col[i]] = col[i];
	}
	for (int i = 1; i <= n; ++ i) {
		colc[id[col[i]]].push_back(i);
	}
	for (int _ = 1; _ <= m; ++ _) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			if (x == y) {
				continue;
			}
			if (colc[id[x]].size() > colc[id[y]].size()) {
				swap(id[x], id[y]);
			}
			modify(id[x], id[y]);
		} else {
			cout << ans << '\n';
		}
	}
}