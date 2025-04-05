#include <bits/stdc++.h>
using namespace std;

using i64 = int64_t;

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	
	constexpr i64 MOD = 998244353;
	auto Pow = [&](i64 a, i64 i) -> i64 {
		a %= MOD;
		i64 ret = 1;
		for (; i > 0; i >>= 1, (a *= a) %= MOD) {
			if (i & 1) {
				(ret *= a) %= MOD;
			}
		}
		return ret;
	};
	auto Inv = [&](i64 x) -> i64 {
		return Pow(x, MOD - 2);
	};

	int n;
	cin >> n;

	i64 a = 0, b = 0, tmp = 1;
	for (int i = 1; i <= n; i ++) {
		i64 x, y;
		cin >> x >> y;
		auto p = (x * Inv(y)) % MOD;
		(a += tmp) %= MOD;
		(b += (tmp * p) % MOD) %= MOD;
		(tmp *= ((1 - p) % MOD + MOD) % MOD) %= MOD;
	}

	cout << (a * Inv(((1 - b) % MOD + MOD) % MOD) % MOD + MOD) % MOD << '\n';
}