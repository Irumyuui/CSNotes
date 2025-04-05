public class Solution
{
    public int MaxPointsInsideSquare(int[][] points, string s)
    {
        int n = points.Length;

        int ans = 0;
        bool check(int len)
        {
            uint vis = 0;
            for (int i = 0; i < n; i++)
            {
                var (x, y) = (points[i][0], points[i][1]);
                x = Math.Abs(x);
                y = Math.Abs(y);
                if (x > len || y > len)
                    continue;
                int c = s[i] - 'a';
                if (((vis >> c) & 1) == 1)
                    return false;
                vis |= (uint)(1 << c);
            }

            int cnt = 0;
            for (int i = 0; i < 32; i++)
                cnt += (int)((vis >> i) & 1);
            ans = Math.Max(ans, cnt);
            return true;
        }

        int l = 0, r = int.MaxValue / 2;
        while (l <= r)
        {
            var mid = l + (r - l) / 2;            
            if (check(mid))
                l = mid + 1;
            else
                r = mid - 1;
        }

        return ans;
    }
}