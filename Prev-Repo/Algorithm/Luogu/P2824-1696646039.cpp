#include <bits/stdc++.h>

#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...)
#endif

template <typename _Ty>
constexpr _Ty inf = std::numeric_limits<_Ty>::max() / 2;
using u8 = uint8_t;
using i64 = int64_t;

using namespace std;

const int N = 2e5 + 10;

struct Node {
    int val, lz;
} seg[N * 4];

void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}
void update(int l, int r, int id, int lz) {
    seg[id].val = (r - l + 1) * lz;
    seg[id].lz = lz;
}
void down(int l, int r, int id) {
    if (auto &lz = seg[id].lz; lz != -1) {
        auto mid = l + (r - l) / 2;
        update(l, mid, id * 2, lz);
        update(mid + 1, r, id * 2 + 1, lz);
        lz = -1;
    }
}

void build(int l, int r, int id, const auto &a, int x) {
    seg[id].lz = -1;
    if (l == r) {
        seg[id].val = x <= a[l];
    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, a, x);
        build(mid + 1, r, id * 2 + 1, a, x);
        rise(id);
    }
}

void apply(int l, int r, int id, int ml, int mr, int lz) {
    if (l == ml && r == mr) {
        update(l, r, id, lz);
    } else {
        auto mid = l + (r - l) / 2;
        down(l, r, id);
        if (mr <= mid) {
            apply(l, mid, id * 2, ml, mr, lz);
        } else if (ml > mid) {
            apply(mid + 1, r, id * 2 + 1, ml, mr, lz);
        } else {
            apply(l, mid, id * 2, ml, mid, lz);
            apply(mid + 1, r, id * 2 + 1, mid + 1, mr, lz);
        }
        rise(id);
    }
}

auto query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        down(l, r, id);
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 +1 , ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}

auto Main() -> void {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i += 1) {
        cin >> a[i];
    }
    struct Opt {
        int opt, l, r;
    };
    vector<Opt> opt_list(m);
    for (auto &[opt, l, r] : opt_list) {
        cin >> opt >> l >> r;
    }

    int pos;
    cin >> pos;

    auto check = [&](int maybe_value) -> bool {
        build(1, n, 1, a, maybe_value);

        for (auto [opt, l, r] : opt_list) {
            auto one_cnt = query(1, n, 1, l, r);
            auto zero_cnt = r - l + 1 - one_cnt;
            if (opt == 0) {
                if (l + zero_cnt - 1 >= l) {
                    apply(1, n, 1, l, l + zero_cnt - 1, 0);
                }
                if (r - one_cnt + 1 <= r) {
                    apply(1, n, 1, r - one_cnt + 1, r, 1);
                }
            } else {
                if (l + one_cnt - 1 >= l) {
                    apply(1, n, 1, l, l + one_cnt - 1, 1);
                }
                if (r - zero_cnt + 1 <= r) {
                    apply(1, n, 1, r - zero_cnt + 1, r, 0);
                }
            }
        }

        return query(1, n, 1, pos, pos) > 0;
    };

    int l = 0, r = inf<int>, tag = -1;
    while (l <= r) {
        auto mid = l + (r - l) / 2;
        if (check(mid)) {
            tag = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    cout << tag << '\n';
}

auto main() -> int {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(15);

    int test = 1;
    // std::cin >> test;

    for (int t = 0; t < test; t += 1) {
        Main();
    }
}
