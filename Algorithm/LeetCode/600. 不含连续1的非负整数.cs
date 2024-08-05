public class Solution
{
    public int FindIntegers(int n)
    {
        var digit = new int[32];
        for (int i = 0; i < 32; i ++) {
            digit[i] = n >> i & 1;
        }

        var dp = new int[32, 2];
        for (int i = 0; i < 32; i ++) {
            for (int j = 0; j < 2; j ++) {
                dp[i, j] = -1;
            }
        }
        // dp[0, 0] = 1;

        int dfs(int pos, int pre, bool isLead, bool isLimit)
        {
            if (pos == -1) {
                return 1;
            } else if (!isLead && !isLimit && dp[pos, pre] != -1) {
                return dp[pos, pre];
            }

            int limit = isLimit ? digit[pos] : 1;
            int ret = 0;
            for (int i = 0; i <= limit; i ++) {
                if (i == 0 && isLead) {
                    ret += dfs(pos - 1, 0, true, isLimit && i == limit);
                } else if (i != 0 && isLead) {
                    ret += dfs(pos - 1, i, false, isLimit && i == limit);
                } else if (pre != 1 || i != 1) {
                    ret += dfs(pos - 1, i, isLead && i == 0, isLimit && i == limit);
                }
            }

            if (!isLead && !isLimit) {
                dp[pos, pre] = ret;
            }
            return ret;
        }

        return dfs(31, 0, true, true);
    }
}