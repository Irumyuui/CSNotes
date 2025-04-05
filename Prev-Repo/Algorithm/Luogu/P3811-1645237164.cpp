#include <bits/stdc++.h>
using namespace std;

template<typename T = long long> T mul(T a, T b, T p) {
    return static_cast<__int128_t>(a) * b % p;
}

long long inv[20000528 + 10];

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, p;
    std::cin >> n >> p;

    inv[1] = 1;

    for (int i = 2; i <= n; ++ i) {
        inv[i] = mul(static_cast<long long>(p - p / i), inv[p % i], static_cast<long long>(p));
    }

    for (int i = 1; i <= n; ++ i) {
        std::cout << inv[i] << '\n';
    }

    return 0;
}