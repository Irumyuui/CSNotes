#include <iostream>
#include <vector>

using namespace std;

int dp[1001];

vector< vector< pair<int, int> > >v(1000, vector< pair<int, int> >());

int main()
{
    int sumw, n, group = -1;
    cin >> sumw >> n;
    for (int i = 0; i < n; ++ i)
    {
        int w, r, g;
        cin >> w >> r >> g;
        v[g].push_back({w, r});
        group = max(group, g);
    }
    for (int i = 1; i <= group; ++ i)
    {
        for (int j = sumw; j >= 0; -- j)
        {
            for (int k = 0; k < v[i].size(); ++ k)
            {
                if (j >= v[i][k].first){
                    dp[j] = max(dp[j], dp[j - v[i][k].first] + v[i][k].second);
                }
            }
        }
    }
    cout << dp[sumw] << endl;
    return 0;
}