#include <iostream>
#include <vector>

using namespace std;

class food
{
    public:
        int size;
        int weigh;
        int power;
};

int dp[50][400][400];

vector<food>v;

int main()
{
    int size, weigh;
    cin >> size >> weigh;
    int n;
    cin >> n;
    v = vector<food>(n + 1);
    for (int i = 1; i <= n; ++ i)
    {
        cin >> v[i].size >> v[i].weigh >> v[i].power;
    }
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = size; j >= 0; -- j)
        {
            for (int k = weigh; k >= 0; -- k)
            {
                if (j >= v[i].size && k >= v[i].weigh){
                    dp[i][j][k] = max(dp[i - 1][j - v[i].size][k - v[i].weigh] + v[i].power, dp[i - 1][j][k]);
                }else{
                    dp[i][j][k] = dp[i - 1][j][k];
                }
            }
        }
    }
    cout << dp[n][size][weigh] << endl;
    return 0;
}