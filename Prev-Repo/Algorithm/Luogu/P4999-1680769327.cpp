#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

using i64 = int64_t;

using namespace std;

constexpr i64 MOD = 1e9 + 7;

void Main() {
	i64 l, r;
	cin >> l >> r;
	
	vector f(20, vector<i64>(9 * 18 + 10, -1));
	auto calc = [&](i64 num) {
		vector<int> digit;
		while (num > 0) {
			digit.emplace_back(num % 10);
			num /= 10;
		}
		auto dfs = [&](auto &&dfs, int pos, int sum, bool limit, bool lead) -> i64 {
			if (pos < 0)
				return sum;
			if (!limit && !lead && f[pos][sum] != -1)
				return f[pos][sum];
			int up = limit ? digit[pos] : 9;
			i64 ret = 0;
			for (int i = 0; i <= up; i ++) 
				(ret += dfs(dfs, pos - 1, sum + i, limit && i == up, lead && i == 0)) %= MOD;
			if (!limit && !lead) 
				f[pos][sum] = ret;
			return ret;
		};
		return dfs(dfs, int(digit.size()) - 1, 0, true, true);
	};
	
	cout << ((calc(r) - calc(l - 1)) % MOD + MOD) % MOD << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);

	int test;
	cin >> test;
	
	while (test --> 0)
		Main();
}