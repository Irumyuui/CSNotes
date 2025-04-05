#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = int64_t;

void Main() {
	i64 n, k;
	cin >> n >> k;

	vector f(64, vector<i64>(k + 1, -1));
	auto calc = [&](i64 n) {
		vector<int> digit;
		while (n > 0) {
			digit.emplace_back(n % 2);
			n /= 2;
		}
		auto dfs = [&](auto &&dfs, int pos, int cnt, bool limit, bool lead) -> i64 {
			if (pos < 0) 
				return cnt == k;
			if (!lead && !limit && f[pos][cnt] != -1)
				return f[pos][cnt];
			int up = limit ? digit[pos] : 1;
			i64 ret = 0;
			for (int i = 0; i <= up; i ++)
				if (i == 1) {
					if (cnt + 1 <= k)
						ret += dfs(dfs, pos - 1, cnt + 1, limit && i == up, lead && i == 0);
				} else {
					ret += dfs(dfs, pos - 1, cnt, limit && i == up, lead && i == 0);
				}
			if (!lead && !limit)
				f[pos][cnt] = ret;
			return ret;
		};
		return dfs(dfs, int(digit.size()) - 1, 0, true, true);
	};

	cout << calc(n) << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	Main();
}