#include <bitset>
#include <vector>

class Solution {
   public:
    bool canPartition(std::vector<int>& nums) {
        constexpr int N = 100 * 100 + 1;

        int s = 0;
        for (auto x : nums) {
            s += x;
        }
        if (s % 2) {
            return false;
        }

        std::bitset<N> dp{1};
        for (auto x : nums) {
            dp |= dp << x;
        }
        return dp[s / 2];
    }
};