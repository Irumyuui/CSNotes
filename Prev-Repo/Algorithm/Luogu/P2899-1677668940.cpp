#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	int n;
	cin >> n;
	vector adj(n + 1, vector<int>());
	for (int i = 1; i < n; i ++) {
		int a, b;
		cin >> a >> b;
		adj[a].emplace_back(b);
		adj[b].emplace_back(a);
	}

	// 0 自己 1 儿子 2 父亲
	vector f(n + 1, vector<int>(3));
	auto dfs = [&](auto &&dfs, int from, int com) -> void {
		f[from][0] = 1;
		int tmp = 0;
		for (auto to : adj[from]) {
			if (to != com) {
				dfs(dfs, to, from);
				f[from][0] += min({f[to][0], f[to][1], f[to][2]});
				f[from][2] += min({f[to][0], f[to][1]});
				tmp += min(f[to][0], f[to][1]);
			}
		}
		f[from][1] = inf<int>;
		for (auto to : adj[from]) {
			if (to != com) {
				f[from][1] = min(f[from][1], f[to][0] + (tmp - min(f[to][0], f[to][1])));
			}
		}
	};
	dfs(dfs, 1, 0);

	debug(f);

	cout << min(f[1][0], f[1][1]) << '\n';
}