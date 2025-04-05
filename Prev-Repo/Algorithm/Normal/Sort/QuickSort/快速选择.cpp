#include <numeric>
#include <span>
#include <utility>
#include <vector>

class Solution {
   public:
    // kth 是 0-based 的
    int quickSelect(std::span<int> sp, int kth) {
        if (sp.size() == 1) {
            return sp.front();
        }

        // 跑一遍快排
        auto pivot = sp[std::midpoint<std::size_t>(0, sp.size())];
        std::size_t l = 0, r = sp.size(), i = 0;
        while (l < r) {
            if (auto ret = sp[l] <=> pivot; ret < 0) {
                std::swap(sp[l++], sp[i++]);
            } else if (ret > 0) {
                std::swap(sp[l], sp[--r]);
            } else {
                l++;
            }
        }

        // 如果在左边，那么就左边处理   
        if (kth < i) {
            return quickSelect(sp.first(i), kth);
        } else if (kth >= r) {
            // 如果在右边，那么去右边
            return quickSelect(sp.last(sp.size() - r), kth - r);
        } else {
            // 否则就是 pivot
            return pivot;
        }
    }

    int majorityElement(std::vector<int>& nums) {
        return quickSelect(nums, nums.size() / 2);
    }
};