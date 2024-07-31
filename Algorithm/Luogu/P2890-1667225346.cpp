#include <bits/stdc++.h>
using namespace std;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n, m;
	cin >> n >> m;
	string s;
	cin >> s;
	vector<int> ned(1 << 8), del(1 << 8);
	for (int i = 0; i < n; i ++) {
		char x;
		cin >> x;
		cin >> ned[x];
		cin >> del[x];
	}
	vector f(m, vector<int>(m, -1));
	auto dfs = [&](auto &&dfs, int l, int r) -> int {
		if (r - l <= 0) {
			return 0;
		}
		if (f[l][r] != -1) {
			return f[l][r];
		}
		// s[l] == s[r] ？能就找子区间的回文串
		int ret = s[l] == s[r] ? dfs(dfs, l + 1, r - 1) : inf<int>;
		ret = min({
			ret,
			dfs(dfs, l + 1, r) + std::min(ned[s[l]], del[s[l]]),  // 加右边，或者删左边
			dfs(dfs, l, r - 1) + std::min(ned[s[r]], del[s[r]])
		});
		return f[l][r] = ret;
	};
	cout << dfs(dfs, 0, m - 1) << '\n';
}