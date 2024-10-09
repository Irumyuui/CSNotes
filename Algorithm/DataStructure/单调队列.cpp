#include <deque>
#include <vector>

class Solution {
   public:
    std::vector<int> maxSlidingWindow(std::vector<int>& nums, int k) {
        std::deque<int> dq;
        std::vector<int> ans;
        ans.reserve(nums.size());

        for (int i = 0; i < nums.size(); i++) {
            while (!dq.empty() && dq.front() <= i - k) {
                dq.pop_front();
            }

            while (!dq.empty() && nums[dq.back()] <= nums[i]) {
                dq.pop_back();
            }
            dq.push_back(i);

            if (i + 1 >= k) {
                ans.emplace_back(nums[dq.front()]);
            }
        }

        return ans;
    }
};
