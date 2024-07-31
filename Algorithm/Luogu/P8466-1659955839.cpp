/* a */
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
	string s;
	cin >> s;
	map<char, int> cnt;
	for (auto x : s) {
		cnt[x] ++;
	}
	if (cnt['X'] && cnt['D']) {
		YES;
		return;
	} 
	for (auto [a, b] : cnt) {
		if (b >= 4) {
			YES;
			return;
		}
	}
	NO;
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	cin >> t;
	while (t --) {
		Solution();
	}
}