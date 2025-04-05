#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector< std::pair<int, int> > v(n);
    for (auto & [l, w] : v)
        std::cin >> l >> w;
    std::sort(v.begin(), v.end(), 
        [](const std::pair<int, int> & a, const std::pair<int, int> & b) {
            return a.first == b.first ? a.second > b.second : a.first > b.first;
        });
    
    
    int ans = 0;
    std::vector<int>dp(n, 0);
    for (int i = 0; i < n; ++ i) {
        for (int j = i; j >= 0; -- j)
            if (v[i].second > v[j].second) 
                dp[i] = std::max(dp[i], dp[j] + 1);
        ans = std::max(dp[i], ans);
    }
    std::cout << ans + 1 << '\n';

    return 0;
}