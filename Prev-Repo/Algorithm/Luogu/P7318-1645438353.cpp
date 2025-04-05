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
    
    ll n, m, k;
    std::cin >> n >> m >> k;

    std::vector<ll>v(10);

    v[1] = n, v[2] = m;

    for (int i = 3; i <= 8; ++ i) {
        v[i] = static_cast<LL>(v[i - 1]) * v[i - 2] % 10;
    }

    ll pos = (k - 3) % 6 + 3;

    std::cout << v[pos];

    return 0;
}