#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE
#include ".vscode/debug.hpp"
#else
#define debug(...)
#endif

using i64 = int64_t;

void Main() {
	vector a(4, vector<i64>{});
	for (auto &x : a) {
		int n;
		cin >> n;
		x.resize(n);
	}
	for (auto &x : a) {
		for (auto &x : x) {
			cin >> x;
		}
	}
	
	i64 ans = 0;
	ranges::for_each(a, [&](auto &&x) {
		auto calc = [](auto &&x) -> i64 {
			auto tot = reduce(x.begin(), x.end());
			vector<i64> f(tot / 2 + 1);
			for (auto &cost : x) {
				for (int j = tot / 2; j >= cost; j --) {
					f[j] = max(f[j], f[j - cost] + cost);
				}
			}

			i64 ret = ranges::max(f);
			return max(ret, tot - ret);
		};
		ans += calc(x);
	});

	cout << ans << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}