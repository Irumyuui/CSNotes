/* P1119 灾后重建 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max() / 2;
using ll = int64_t;

void Solution() {
	int n, m;
	cin >> n >> m;
	vector<int> ok(n);
	unordered_map<int,vector<int>> t;
	vector<int> tl(0);
	for (int i = 0; i < n; ++ i) {
		int x;
		cin >> x;
		t[x].push_back(i);
		tl.push_back(x);
		ok[i] = x;
	}
	ranges::sort(tl);
	tl.erase(unique(tl.begin(), tl.end()), tl.end());
	vector<vector<int>> f(n, vector<int>(n, inf<int>));
	for (int i = 0; i < n; ++ i) {
		f[i][i] = 0;
	}
	for (int i = 0; i < m; ++ i) {
		int a, b, w;
		cin >> a >> b >> w;
		f[a][b] = f[b][a] = w;
	}
	auto last = tl.begin();
	auto calc = [&](int tt) {
		if (!t.count(tt)) {
			return;
		}
		for (auto k : t[tt]) {
			for (int i = 0; i < n; ++ i) {
				for (int j = 0; j < n; ++ j) {
					f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
				}
			}
		}
	};
	int q;
	cin >> q;
	while (q --) {
		int a, b, ed;
		cin >> a >> b >> ed;
		while (last != tl.end() && *last <= ed) {
			calc(*last);
			last ++;
		}
		if (ok[a] <= ed && ok[b] <= ed && f[a][b] != inf<int>) {
			cout << f[a][b] << '\n';
		} else {
			cout << -1 << '\n';
		}
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}