#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <ranges>

using i64 = int64_t;

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    i64 n;
    std::cin >> n;

    auto GetBitDigit = [](i64 n) {
        std::vector<int> ret;
        while (n > 0) {
            ret.emplace_back(n & 1);
            n >>= 1;
        }
        return ret;
    };
    auto digit = GetBitDigit(n);

    std::vector dp(digit.size(), std::vector<i64>(digit.size(), -1));
    constexpr i64 MOD = 10000007;

    auto dfs = [&](auto &dfs, int pos, int bit_one_cnt, bool lead, bool limit) -> i64 {
        if (pos == -1) {
            if (bit_one_cnt == 0) {
                return 1;
            } else {
                return bit_one_cnt;
            }
        } else if (!lead && !limit && dp[pos][bit_one_cnt] != -1) {
            return dp[pos][bit_one_cnt];
        }

        i64 ret = 1;
        auto Lim = limit ? digit[pos] : 1;
        for (int d = 0; d <= Lim; d ++) {
            (ret *= dfs(dfs, pos - 1, bit_one_cnt + d, lead && d == 0, limit && d == Lim)) %= MOD;
        }

        if (!lead && !limit) {
            dp[pos][bit_one_cnt] = ret;
        }
        return ret;
    };

    std::cout << dfs(dfs, (int)digit.size() - 1, 0, true, true) << '\n';
}