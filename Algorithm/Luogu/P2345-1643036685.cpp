#include <bits/stdc++.h>

using namespace std;

#define all(x) begin(x), end(x)

typedef long long LL;

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<pair<LL, LL>>v(n);
    for (auto &it : v)
    {
        cin >> it.first >> it.second;
    }
    LL ans = 0;
    for (int i = 0; i < n; ++ i)
    {
        for (int j = i + 1; j < n; ++ j)
        {
            ans += max(v[i].first, v[j].first) * llabs(v[i].second - v[j].second);
        }
    }
    cout << ans;
    return 0;
}