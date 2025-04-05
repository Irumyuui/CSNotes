#include <algorithm>
#include <limits>
#include <string>
#include <vector>

template <typename T>
constexpr T inf = std::numeric_limits<T>::max() / 2;

class Solution {
   public:
    int minDistance(std::string word1, std::string word2) {
        auto dp = std::vector(word1.size(), std::vector<int>(word2.size(), -1));

        auto dfs = [&](auto &dfs, int i, int j) -> int {
            if (i < 0 || j < 0) {
                return std::max(i, j) + 1;
            }
            if (dp[i][j] != -1) {
                return dp[i][j];
            }
            // 一样，保留
            if (word1[i] == word2[j]) {
                return dp[i][j] = dfs(dfs, i - 1, j - 1);
            }

            return dp[i][j] = std::min({
                dfs(dfs, i - 1, j),  // 删掉自己，自己下一个匹配
                dfs(dfs, i, j - 1),  // 自己插入，匹配对方下一个
                dfs(dfs, i - 1, j - 1)  // 自己替换，一起下一个
            }) + 1;
        };

        return dfs(dfs, static_cast<int>(word1.size()) - 1, static_cast<int>(word2.size()) - 1);
    }
};