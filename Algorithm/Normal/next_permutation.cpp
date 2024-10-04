#include <utility>
#include <vector>

class Solution {
   public:
    void nextPermutation(std::vector<int>& nums) {
        if (nums.size() <= 1) {
            return;
        }

        // 先找到一个位置，使得 nums[i] < nums[i + 1]
        int i = static_cast<int>(nums.size()) - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        if (i < 0) {
            for (int l = 0, r = static_cast<int>(nums.size()) - 1; l < r;
                 l++, r--) {
                std::swap(nums[l], nums[r]);
            }
            return;
        }

        // 再找到一个位置，使得 nums[i] < nums[j]
        int j = static_cast<int>(nums.size()) - 1;
        while (j > i && nums[i] >= nums[j]) {
            j--;
        }

        // 交换这两两个位置，然后翻转后面的序列
        std::swap(nums[i], nums[j]);

        for (int l = i + 1, r = static_cast<int>(nums.size()) - 1; l < r;
             l++, r--) {
            std::swap(nums[l], nums[r]);
        }
    }
};
