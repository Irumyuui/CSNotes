public class Solution
{
    public int MinRectanglesToCoverPoints(int[][] points, int w)
    {
        var x = points.Select(item => item[0]).Distinct().Order().ToArray();

        if (x.Length == 1)
            return 1;

        int cnt = 0, left = x[0];
        for (int i = 1; i < x.Length; i++)
        {
            if (x[i] - left > w)
            {
                cnt++;
                left = x[i];
            }
        }

        return cnt + 1;
    }
}