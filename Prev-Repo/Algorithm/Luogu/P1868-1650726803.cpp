#include <bits/stdc++.h>
using namespace std;

#define all(x) std::begin(x), std::end(x)

const int N = 3e6 + 30;
vector<int> c[N];

signed main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    cin >> n;
    int m = 0;
    for (int i = 0; i < n; ++ i) {
        int x, y;
        cin >> x >> y;
        m = max(m, y);
        c[x].push_back(y);
    }

    vector<int> dp(m + 2, 0);
    for (int i = m; i >= 0; -- i) {
        dp[i] = dp[i + 1];
        for (auto k : c[i]) {
            dp[i] = max(dp[i], dp[k + 1] + (k - i + 1));
        }
    }
    cout << dp[0] << '\n';

    return 0;
}