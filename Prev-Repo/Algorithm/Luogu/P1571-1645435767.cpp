#include <bits/stdc++.h>

#define all(container) std::begin(container), std::end(container)
#define range(iterator, container) for (auto &iterator : container)
#define crange(iterator, container) for (const auto &iterator : container)
#define cauto const auto
#define clear(array) std::memset(array, 0, sizeof(array))

using ll = long long;
using LL = __int128_t;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    std::unordered_map<int, bool>vis;

    int n, m;
    std::cin >> n >> m;

    std::vector<int>a(n), b(m), ans;

    range(it, a) {
        std::cin >> it;
        vis[it] = false;
    }

    range(it, b) {
        std::cin >> it;
        vis[it] = true;
    }

    crange(it, a) {
        if (vis[it]) {
            std::cout << it << ' ';
        }
    }

    return 0;
}