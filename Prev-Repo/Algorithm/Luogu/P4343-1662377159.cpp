/* P4343 [SHOI2015]自动刷题机 */
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include <debug.h>
#else
#define debug(...) 114514
#endif
#define YES std::cout << "YES\n"
#define NO std::cout << "NO\n"
template <typename T> constexpr T inf = std::numeric_limits<T>::max();
using ll = int64_t;

void Solution() {
	ll n, k;
	cin >> n >> k;
	vector<ll> a(n);
	for (auto &x : a) {
		cin >> x;
	}

	auto calc = [&](ll tag) {
		ll tmp = 0;
		ll cnt = 0;
		for (const auto &x : a) {
			tmp = max<ll>(tmp + x, 0);
			if (tmp >= tag) {
				cnt ++;
				tmp = 0;
			}
		}
		return cnt;
	};
	
	ll mini = -1, maxi = -1;
	{
		ll l = 1, r = inf<ll>, ans = -1;
		while (l <= r) {
			ll mid = l + ((r - l) >> 1);
			auto ret = calc(mid);
			if (ret <= k) {
				r = mid - 1;
				if (ret == k) {
					ans = mid;
				}
			} else {
				l = mid + 1;
			}
		}
		mini = ans;
	}
	{
		ll l = 1, r = inf<ll>, ans = -1;
		while (l <= r) {
			ll mid = l + ((r - l) >> 1);
			auto ret = calc(mid);
			if (ret >= k) {
				l = mid + 1;
				if (ret == k) {
					ans = mid;
				}
			} else {
				r = mid - 1;
			}
		}
		maxi = ans;
	}
	if (mini == -1 || maxi == -1) {
		cout << -1;
	} else {
		cout << mini << ' ' << maxi << '\n';
	}
}

int32_t main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	std::cout << std::fixed << std::setprecision(12);
	Solution();
}