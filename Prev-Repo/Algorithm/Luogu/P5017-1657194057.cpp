#include <bits/stdc++.h>
using namespace std;

const int N = 501, M = 5e4 + 1;
int n, m;
int t[N], f[N][M];

void Solution() {
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> t[i];
	}
	sort(t + 1, t + 1 + n);
	memset(f, -1, sizeof f);
	function<int(int,int)> dfs = [&](int id, int stamp) -> int {
		if (id > n) {
			return 0;
		}
		if (stamp < t[id]) {
			return dfs(id, t[id]);
		}
		if (f[id][stamp - t[id]] != -1) {
			return f[id][stamp - t[id]];
		}
		// 能拉就拉
		int nuse = 0, last = id;
		for (; last <= n && t[last] <= stamp; ++ last) {
			nuse += t[last];
		}
		// 等到某一个人才发车
		int ret = (last - id) * stamp - nuse + dfs(last, stamp + m);
		for (; last <= n; ++ last) {
			nuse += t[last];
			ret = min({
				ret,
				(last - id + 1) * t[last] - nuse + dfs(last + 1, t[last] + m)
			});
		}
		return f[id][stamp - t[id]] = ret;
	};
	cout << dfs(1, 0);
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}