#include <bits/stdc++.h>

template<typename T = long long> inline T mul(T a, T b, T p) {
    return static_cast<__int128_t>(a) * b % p;
}

template<typename T = long long> inline T power(T a, T i, T p) {
    T res = 1 % p;
    while (i) {
        if (i & 1)
            res = mul(res, a, p);
        a = mul(a, a, p);
        i >>= 1;
    }
    return res;
}

long long BSGS(long long a, long long b, long long p) {
    b %= p;
    std::unordered_map<long long, long long>Bi;

    long long t = std::sqrt(p) + 1;

    for (long long B = 0; B < t; ++ B) {
        long long baB = mul(b, power(a, B, p), p);
        Bi[baB] = B;
    }

    long long at = power(a, t, p);
    for (long long A = 0; A < t; ++ A) {
        long long aAt = power(at, A, p);
        if (Bi.count(aAt)) {
            long long ans = A * t - Bi[aAt];
            if (ans >= 0) {
                return ans;
            }
        }      
    }

    return -1;
}

long long Exgcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    long long d = Exgcd(b, a % b, x, y);
    long long tmp = x;
    x = y;
    y = tmp - a / b * y;
    return d;
}

bool Ce(long long a, long long c, long long p, long long &x, long long &y) {
    long long d = Exgcd(a, p, x, y);
    
    if (c % d != 0) {
        return false;
    }

    long long t = c / d;
    x *= t; y *= t;

    return true;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T, K;
    std::cin >> T >> K;

    if (K == 1) {
        while (T --) {
            long long y, z, p;
            std::cin >> y >> z >> p;

            std::cout << power(y, z, p) << '\n';
        }
    } else if (K == 2) {
        while (T --) {
            long long y, z, p;
            std::cin >> y >> z >> p;
            
            long long x_, y_;
            if (Ce(y, z, p, x_, y_)) {
                x_ = (x_ % p + p) % p;
                std::cout << x_ << '\n';
            } else {
                std::cout << "Orz, I cannot find x!\n";
            }
        }
    } else {
        while (T --) {
            long long y, z, p;
            std::cin >> y >> z >> p;

            if (y % p == 0 && z % p != 0) {
                std::cout << "Orz, I cannot find x!\n";
                continue;
            }

            long long ans = BSGS(y, z, p);

            if (ans == -1) {
                std::cout << "Orz, I cannot find x!\n";
            } else {
                std::cout << ans << '\n';
            }
        }
    }

    return 0;
}