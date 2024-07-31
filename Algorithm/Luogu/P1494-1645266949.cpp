#include <bits/stdc++.h>

struct query{
    int l, r;
    // long long a, b;  // a / b
    int id;
};

struct ANS{
    long long a, b;
};

const int MAXN = 5e5 + 10;
int maxn = 0;
long long sum = 0;
int c[MAXN], cnt[MAXN];

inline void addc(int id) {
    sum += cnt[id];
    ++ cnt[id];
}

inline void delc(int id) {
    -- cnt[id];
    sum -= cnt[id];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++ i) {
        std::cin >> c[i];
    }

    maxn = std::sqrt(n);
    std::vector<query>v(m);
    std::vector<ANS>ans(m);
    for (int i = 0; i < m; ++ i) {
        std::cin >> v[i].l >> v[i].r;
        v[i].id = i;
    }

    std::sort(v.begin(), v.end(), [](const query &a, const query &b){
        if (a.l / maxn != b.l / maxn) {
            return a.l < b.l;
        }
        return (a.l / maxn) & 1 ? a.r < b.r : a.r > b.r;
    });


    int l = 1, r = 0;
    for (const auto &[ll, rr, id] : v) {
        if (ll == rr) {
            ans[id].a = 0;
            ans[id].b = 1;
            continue;
        }

        while (l > ll) {
            addc(c[-- l]);
        }
        while (r < rr) {
            addc(c[++ r]);
        }
        while (l < ll) {
            delc(c[l ++]);
        }
        while (r > rr) {
            delc(c[r --]);
        }

        ans[id].a = sum;
        ans[id].b = static_cast<__int128_t>(r - l + 1) * (r - l) / 2; 
    }

    for (const auto &[a, b] : ans) {
        if (a == 0) {
            std::cout << "0/1" << '\n';
            continue;
        }

        // std::cout << a << '/' << b << '\n';

        long long d = std::__gcd(a, b);
        long long a_ = a / d, b_ = b / d;
        std::cout << a_ << '/' << b_ << '\n';
    }

    return 0;
}