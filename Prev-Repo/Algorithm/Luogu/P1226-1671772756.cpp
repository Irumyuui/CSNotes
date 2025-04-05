#include <iostream>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int64_t a, b, p;
    std::cin >> a >> b >> p;
    auto qp = [](auto a, auto i, auto p) {
        decltype(a) ret = 1 % p;
        while (i > 0) {
            if (i & 1) {
                (ret *= a) %= p;   
            }
            (a *= a) %= p;
            i >>= 1;
        }
        return ret;
    };
    std::cout << a << "^" << b << " mod " << p << "=" << qp(a, b, p);
}