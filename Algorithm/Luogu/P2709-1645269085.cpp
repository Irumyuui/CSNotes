#include <bits/stdc++.h>

struct query{
    int l, r;
    int id;
};

const int MAXN = 1e6 + 10;
int num[MAXN];
long long cnt[MAXN], sum = 0;
int tot = 0;

inline void addn(int num){
    sum += cnt[num] * 2 + 1;
    ++ cnt[num];
}

inline void deln(int num) {
    sum -= cnt[num] * 2 - 1;
    -- cnt[num];
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    for (int i = 1; i <= n; ++ i) {
        std::cin >> num[i];
    }

    std::vector<long long>ans(m);
    std::vector<query>v(m);

    for (int i = 0; i < m; ++ i) {
        std::cin >> v[i].l >> v[i].r;
        v[i].id = i;
    }    

    tot = std::sqrt(n);
    sort(v.begin(), v.end(), [](const query &a, const query &b){
        if (a.l / tot != b.l / tot) {
            return a.l < b.l;
        }
        return (a.l / tot) & 1 ? a.r < b.r : a.r > b.r;
    });

    int l = 1, r = 0;
    for (const auto &[ll, rr, id] : v) {
        if (ll == rr) {
            ans[id] = 1;
            continue;
        }

        while (l > ll) {
            addn(num[-- l]);
        }
        while (r < rr) {
            addn(num[++ r]);
        }
        while (l < ll) {
            deln(num[l ++]);
        }
        while (r > rr) {
            deln(num[r --]);
        }

        ans[id] = sum;
    }

    for (const auto &x : ans) {
        std::cout << x << '\n';
    }

    return 0;
}