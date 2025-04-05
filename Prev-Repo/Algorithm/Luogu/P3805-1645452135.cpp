#include <bits/stdc++.h>

#define all(container) std::begin(container), std::end(container)
#define range(iterator, container) for (auto &iterator : container)
#define crange(iterator, container) for (const auto &iterator : container)
#define cauto const auto
#define clear(array) std::memset(array, 0, sizeof(array))

using ll = long long;
using LL = __int128_t;

const int MAXN = 4e7 + 10;

char str[MAXN];
int ph[MAXN];

inline int inti() {
    char ch;

    int m = 0;

    str[m ++] = '(';
    str[m ++] = '-';

    while (std::cin >> ch) {
        str[m ++] = ch;
        str[m ++] = '-';
    }

    str[m ++] = ')';

    return m;
}

inline int manacher(int len) {
    int pos = 0, rlim = 0, ans = 0;

    for (int i = 1; i < len; ++ i) {
        if (i < rlim) {
            ph[i] = std::min(ph[(pos << 1) - i], rlim - i);
        } else {
            ph[i] = 1;
        }

        while (str[i + ph[i]] == str[i - ph[i]]) {
            ++ ph[i];
        }

        if (i + ph[i] > rlim) {
            rlim = i + ph[i];
            pos = i;
        }

        ans = std::max(ans, ph[i]);
    }

    return ans - 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0); std::cout.tie(0);
    
    int ans = manacher(inti());

    std::cout << ans << '\n';

    return 0;
}