#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

vector<int>dp;
vector<int>missile;

int main()
{
    int x;
    while (cin >> x)
        missile.push_back(x);
    dp = vector<int>(missile.size(), 1);
    int res = 1;
    for (int i = 1; i < missile.size(); ++ i)
    {
        for (int j = i - 1; j >= 0; -- j)
        {
            if (missile[i] <= missile[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    cout << res << endl;
    res = 1;
    fill(dp.begin(), dp.end(), 1);
    for (int i = 1; i < missile.size(); ++ i)
    {
        for (int j = i - 1; j >= 0; -- j)
        {
            if (missile[i] > missile[j]){
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        res = max(res, dp[i]);
    }
    cout << res << endl;
    return 0;
}