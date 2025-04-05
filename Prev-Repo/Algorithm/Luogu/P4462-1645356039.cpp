#include <bits/stdc++.h>

struct query {
    int l, r, id, block;

    bool operator < (const query &x) const {
        if (block != x.block) {
            return l < x.l;
        }
        return block & 1 ? r < x.r : r > x.r;
    }
};

const int MAXN = 1e7 + 10;
long long cnt[MAXN], sum;
int c[MAXN];

int k;

inline void add(int num) {
    ++ cnt[num];
    sum += cnt[num ^ k];
}

inline void del(int num) {
    -- cnt[num];
    sum -= cnt[num ^ k];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m >> k;

    c[0] = 0;
    for (int i = 1; i <= n; ++ i) {
        std::cin >> c[i];
        c[i] ^= c[i - 1];
    }

    std::vector<long long>ans(m);
    std::vector<query>v(m);

    int tot = std::sqrt(n);

    for (int i = 0; i < m; ++ i) {
        std::cin >> v[i].l >> v[i].r;
        v[i].block = v[i].l / tot;
        v[i].l --;
        v[i].id = i;
    }

    std::sort(v.begin(), v.end());

    int l = 1, r = 0;
    for (const auto &[ll, rr, id, block] : v) {
        while (l > ll) {
            add(c[-- l]);
        }
        while (r < rr) {
            add(c[++ r]);
        }
        while (l < ll) {
            del(c[l ++]);
        }
        while (r > rr) {
            del(c[r --]);
        }

        ans[id] = sum;
    }

    for (const auto &x : ans) {
        std::cout << x << '\n';
    }

    return 0;
}