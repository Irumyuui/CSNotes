#include <bits/stdc++.h>

using ll = long long;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll M, S, T;
    std::cin >> M >> S >> T;

    ll s1 = 0, s2 = 0;
    // bool ok = false;
    for (int i = 1; i <= T; ++ i) {
        s2 += 17;
        if (M >= 10) {
            s1 += 60;
            M -= 10;
        } else {
            M += 4;
        }
        if (s1 > s2) {
            s2 = s1;
        }
        if (s1 > S || s2 > S) {
            // ok = true;
            // break;

            std::cout << "Yes" << '\n' << i << '\n';
            return 0;
        }
    }

    std::cout << "No" << '\n' << std::max(s1, s2) << '\n';

    // if (ok) {
    //     std::cout << "Yes" << '\n';
    // } else {
    //     std::cout << "No" << '\n';
    // }

    return 0;
}