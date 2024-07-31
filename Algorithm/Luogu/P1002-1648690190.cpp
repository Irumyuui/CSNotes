#include <bits/stdc++.h>

using ll = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int mx, my, n, m;
    // std::cin >> mx >> my >> n >> m;
    std::cin >> n >> m >> mx >> my;
    mx ++;
    my ++;

    std::vector< std::vector< std::pair<ll, bool> > > dp(n + 2, 
                                std::vector< std::pair<ll, bool> > (m + 2, {0, true}));
    
    auto check = [=] (int x, int y) {
        return x > 0 && x <= n + 1 && y > 0 && y <= m + 1;
    };

    if (check(mx - 1, my - 2)) {
        dp[mx - 1][my - 2].second = false;
    }
    if (check(mx - 2, my - 1)) {
        dp[mx - 2][my - 1].second = false;
    }
    if (check(mx + 1, my - 2)) {
        dp[mx + 1][my - 2].second = false;
    }
    if (check(mx + 2, my - 1)) {
        dp[mx + 2][my - 1].second = false;
    }

    if (check(mx - 1, my + 2)) {
        dp[mx - 1][my + 2].second = false;
    }
    if (check(mx - 2, my + 1)) {
        dp[mx - 2][my + 1].second = false;
    }
    if (check(mx + 1, my + 2)) {
        dp[mx + 1][my + 2].second = false;
    }
    if (check(mx + 2, my + 1)) {
        dp[mx + 2][my + 1].second = false;
    }

    if (check(mx, my)) {
        dp[mx][my].second = false;
    }

    dp[1][1].first = 1;
    for (int i = 1; i <= n + 1; ++ i) {
        for (int j = 1; j <= m + 1; ++ j) {
            // std::cerr << dp[i][j].second << ' ';
            if (!dp[i][j].second)
                continue;
            dp[i][j].first += (dp[i - 1][j].second ? dp[i - 1][j].first : 0) 
                            + (dp[i][j - 1].second ? dp[i][j - 1].first : 0);
        }
        // std::cerr << '\n';
    }
    std::cout << dp[n + 1][m + 1].first << '\n';

    return 0;
}