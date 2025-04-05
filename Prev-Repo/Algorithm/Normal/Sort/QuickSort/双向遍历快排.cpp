#include <numeric>
#include <span>
#include <utility>
#include <vector>

class Solution {
   public:
    void quickSort(std::span<int> sp) {
        if (sp.size() <= 1) {
            return;
        }

        int pivot = sp[std::midpoint<std::size_t>(0, sp.size())];
        std::size_t l = 0, r = sp.size(), i = 0;
        while (l < r) {
            if (sp[l] < pivot) {  // 如果这个元素小于 pivot ，交换到左边
                std::swap(sp[l++], sp[i++]);
            } else if (sp[l] > pivot) {  // 如果这个元素大于 pivot ，交换到右边
                std::swap(sp[l], sp[--r]);
            } else {  // 如果这个元素等于 pivot ，不用管
                l++;
            }
        }

        // [i + 1, r] 这边的序列是有序的，不用管
        quickSort(sp.first(i));
        quickSort(sp.last(sp.size() - r));
    }

    void sortColors(std::vector<int>& nums) { quickSort(nums); }
};