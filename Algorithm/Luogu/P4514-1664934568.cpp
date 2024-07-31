/* P4514 上帝造题的七分钟 */
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
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;
using ld = long double;

const int N = 2050;
int n, m;
int a[N][N], b[N][N], c[N][N], d[N][N];

void add(int x, int y, int v) {
	for (int i = x; i <= n; i += i & -i) {
		for (int j = y; j <= m; j += j & -j) {
			a[i][j] += v;
			b[i][j] += (x - 1) * v;
			c[i][j] += (y - 1) * v;
			d[i][j] += (x - 1) * (y - 1) * v;
		}
	}
}
int query(int x, int y) {
	int ret = 0;
	for (int i = x; i > 0; i -= i & -i) {
		for (int j = y; j > 0; j -= j & -j) {
			ret += x * y * a[i][j]
				- y * b[i][j]
				- x * c[i][j]
				+ d[i][j];
		}
	}
	return ret;
}

void Solution() {
	char opt;
	cin >> opt >> n >> m;
	while (cin >> opt) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		if (opt == 'L') {
			int v;
			cin >> v;
			add(x1, y1, v);
			add(x1, y2 + 1, -v);
			add(x2 + 1, y1, -v);
			add(x2 + 1, y2 + 1, v);
		} else {
			cout << 
				query(x2, y2) 
				- query(x1 - 1, y2) 
				- query(x2, y1 - 1) 
				+ query(x1 - 1, y1 - 1)
			<< '\n';
		}
	}	
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	// int t; std::cin >> t; while (t --> 0)
		Solution();
}