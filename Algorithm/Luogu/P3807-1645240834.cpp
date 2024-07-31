#include <bits/stdc++.h>

template<typename T = long long> inline T mul(T a, T b, T p) {
    return static_cast<__int128_t>(a) * b % p;
}

template<typename T = long long> T Exgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    T d = Exgcd(b, a % b, x, y), t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

template<typename T = long long> inline T inv(T a, T p) {
    T x, y;
    Exgcd(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}

inline long long C(long long m, long long n, long long p) {
    long long a = 1, b = 1;
    for (long long i = n; i > n - m; -- i) {
        a = mul(a, i, p);
    }
    for (long long i = 2; i <= m; ++ i) {
        b = mul(b, i, p);
    }
    return mul(a, inv(b, p), p);
}

long long Lucas(long long m, long long n, long long p) {
    if (n == 0) {
        return 1;
    }
    return mul(C(m % p, n % p, p), Lucas(m / p, n / p, p), p);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    while (t --) {
        long long n, m, p;
        std::cin >> n >> m >> p;

        std::cout << Lucas(n, n + m, p) << '\n';
    }

    return 0;
}