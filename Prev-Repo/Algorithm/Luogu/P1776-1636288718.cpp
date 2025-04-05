#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

typedef long long LL;
typedef pair<LL, LL> PLL;
typedef pair<int, int> PII;

class goods
{
    public:
        int value, weight, cnt;
        goods() = default;
        goods(const int &val, const int &wei, const int &cnt)
        {
            this->value = val;
            this->weight = wei;
            this->cnt = cnt;
        }
};

vector<goods>g;
vector<LL>dp(40005, 0);

int main()
{
    int n, sumweight;
    cin >> n >> sumweight;
    g.push_back(goods());
    for (int i = 0; i < n; ++ i)
    {
        int val, wei, cnt;
        cin >> val >> wei >> cnt;
        for (int i = 1; i <= cnt; i <<= 1)
        {
            cnt -= i;
            g.push_back(goods(val * i, wei * i, i));
        }
        if (cnt > 0){
            g.push_back(goods(val * cnt, wei * cnt, cnt));
        }
    }
    for (int i = 1; i < g.size(); ++ i)
    {
        for (int j = sumweight; j >= g[i].weight; -- j)
        {
            dp[j] = max(dp[j], dp[j - g[i].weight] + g[i].value);
        }
    }
    cout << dp[sumweight];
    return 0;
}