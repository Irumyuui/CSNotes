#include <algorithm>
#include <string>
#include <vector>

class Solution {
   public:
    int longestCommonSubsequence(std::string text1, std::string text2) {
        int n = text1.size(), m = text2.size();
        auto dp = std::vector(n + 1, std::vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (text1[i] == text2[j]) {
                    dp[i + 1][j + 1] = std::max({dp[i][j] + 1, dp[i][j + 1], dp[i + 1][j]});
                } else {
                    dp[i + 1][j + 1] = std::max(dp[i][j + 1], dp[i + 1][j]);
                }
            }
        }

        return dp[n][m];
    }
};