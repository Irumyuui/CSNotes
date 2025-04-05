/* P3558 [POI2013]BAJ-Bytecomputer */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
#define all(x) std::begin(x), std::end(x)
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2 + std::numeric_limits<T>::max() / 4;
using ll = int64_t;
using ld = long double;

const int N = 1e6 + 10;

int f[N][3], a[N];
int n;

int dfs(int id, int st) {
	if (id >= n) {
		return 0;
	}
	if (~f[id][st]) {
		return f[id][st];
	}
	int ret = inf<int>;
	if (st == 1) {
		if (id + 1 < n && a[id + 1] == 0) {
			return inf<int>;
		}
		ret = dfs(id + 1, a[id + 1]);
	} else if (st == 2) {
		if (id + 1 >= n) {
			ret = 0;
		} else {
			ret = dfs(id + 1, st) + st - a[id + 1];
		}
	} else {
		if (id + 1 < n) {
			if (a[id + 1] == 2) {
				ret = min({
					dfs(id + 1, 2) + 0,
					dfs(id + 1, 1) + 1,
					dfs(id + 1, 0) + 2
				});
			} else if (a[id + 1] == 1) {
				ret = min({
					dfs(id + 1, 1) + 0,
					dfs(id + 1, 0) + 1
				});
			} else {
				ret = dfs(id + 1, 0);
			}
		} else {
			ret = 0;
		}
	}
	ret = min(ret, inf<int>);
	return f[id][st] = ret;
}

void Solution() {
	cin >> n;
	for (int i = 0; i < n; i ++) {
		cin >> a[i];
		a[i] ++;
	}
	memset(f, -1, sizeof(f));
	int ans = dfs(0, a[0]);
	if (ans >= inf<int>) {
		cout << "BRAK\n";
	} else {
		cout << ans << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}