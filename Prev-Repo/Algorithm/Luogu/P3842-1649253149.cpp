#include <bits/stdc++.h>

using std::max;
using std::min;
using std::abs;
using std::ceil;

struct Node {
    int l, r;
    Node(int l = 0, int r = 0) : l(l), r(r) {}
};


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector< std::array<int, 2> > dp(n + 1, {0, 0});
    std::vector<Node> v(n + 1);

    // v[0] = {1, 1};
    for (int i = 1; i <= n; ++ i)
        std::cin >> v[i].l >> v[i].r;

    dp[1][0] = v[1].r - 1 + v[1].r - v[1].l;
    dp[1][1] = v[1].r - 1;
    for (int i = 2; i <= n; ++ i) {
        dp[i][0] = min(dp[i - 1][0] + abs(v[i - 1].l - v[i].r) ,dp[i - 1][1] + abs(v[i - 1].r - v[i].r)) + abs(v[i].r - v[i].l) + 1;
        dp[i][1] = min(dp[i - 1][0] + abs(v[i - 1].l - v[i].l), dp[i - 1][1] + abs(v[i - 1].r - v[i].l)) + abs(v[i].r - v[i].l) + 1;

    }

    std::cout << min(dp[n][0] + abs(v[n].l - n), dp[n][1] + abs(v[n].r - n));

    return 0;
}