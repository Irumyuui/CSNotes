/* P3201 [HNOI2009] 梦幻布丁 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES cout << "YES\n"
#define NO cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

const int N = 1e6 + 10;
int a[N], ans = 0;
vector<int> col[N];

void Solution() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> a[i];
		col[a[i]].push_back(i);
	}
	for (int i = 1; i <= n + 1; ++ i) {
		ans += a[i - 1] != a[i];
	}

	auto calc = [&](int i, int c) {
		ans -= (a[i] != a[i - 1]) + (a[i] != a[i + 1]);
		a[i] = c;
		ans += (a[i] != a[i - 1]) + (a[i] != a[i + 1]);
	};
	auto Merge = [&](int x, int y) {
		if (x == y) return;
		if (col[x].size() > col[y].size()) swap(col[x], col[y]);
		if (col[y].empty()) return;
		int c = a[col[y][0]];
		for (auto i : col[x]) {
			calc(i, c);
			col[y].push_back(i);
		}
		col[x].clear();
	};

	for (int i = 1; i <= m; ++ i) {
		int opt;
		cin >> opt;
		if (opt == 1) {
			int x, y;
			cin >> x >> y;
			Merge(x, y);
		} else {
			cout << ans - 1 << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}