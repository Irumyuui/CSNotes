#include <bits/stdc++.h>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int>v(n);

    for (auto &it : v) {
        std::cin >> it;
        it = std::abs(it);
    }

    int ans = 0;

    for (const auto &it : v) {
        ans = std::__gcd(ans, it);
    }

    std::cout << ans;

    return 0;
}