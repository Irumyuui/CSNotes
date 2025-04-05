/* P3375 【模板】KMP字符串匹配 */
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

void Solution() {
	string s, t;
	cin >> s >> t;
	vector<int> nex(t.size(), -1);
	for (int i = 1, k = -1; i < t.size(); ++ i) {
		while (k > -1 && t[k + 1] != t[i]) {
			k = nex[k];
		}
		if (t[k + 1] == t[i]) {
			k ++;
		}
		nex[i] = k;
	}
	vector<int> ret;
	for (int i = 0, k = -1; i < s.size(); ++ i) {
		while (k > -1 && t[k + 1] != s[i]) {
			k = nex[k];
		}
		if (t[k + 1] == s[i]) {
			k ++;
		}
		if (k + 1 == int(t.size())) {
			ret.push_back(i - k);
			k = nex[k];
		}
	}
	for (auto x : ret) {
		cout << x + 1 << '\n';
	}
	for (auto x : nex) {
		cout << x + 1 << ' ';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Solution();
}