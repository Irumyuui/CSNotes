#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif

using namespace std;
using ll = long long;
template <class T> constexpr T inf = std::numeric_limits<T>::max() / 2;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int n; ll m;
	cin >> n >> m;
	vector<int> cnt(n), cost(n);
	for (auto &x : cnt) {
		cin >> x;
	} 
	for (auto &x : cost) {
		cin >> x;
	}
	int mx = 0;
	for (int i = 0; i < n; ++ i) {
		mx += cnt[i] * cost[i];
	}
	vector<ll> f(mx + 1, 0);
	f[0] = 1;
	for (int i = 0; i < n; ++ i) {
		for (int j = mx; j >= 0; -- j) {
			for (int k = 1; k <= cnt[i] && k * cost[i] <= j; ++ k) {
				f[j] = max(f[j], f[j - k * cost[i]] * k);
			}
		}
	}
	for (int i = 0; i <= mx; i ++) {
		if (f[i] >= m) {
			cout << i;
			break;
		}
	}
	debug(f);
}