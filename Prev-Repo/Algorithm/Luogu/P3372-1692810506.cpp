#include "bits/stdc++.h"

using i64 = int64_t;

constexpr int N = 1e5 + 10;

struct Info {
    i64 val;
    Info(i64 val = 0) : val(val) {

    }
    Info operator + (const Info &o) const {
        return Info {
            val + o.val,
        };
    }
};
struct Lazy {
    i64 add;
    Lazy(i64 add = 0) : add(add) {
        
    }
};
struct Node {
    Info val;
    Lazy lz;
} seg[N * 2];

void rise(int l, int r, int id) {
    auto mid = l + ((r - l) >> 1);
    seg[id].val = seg[mid * 2].val + seg[mid * 2 + 1].val;
}
void update(int l, int r, int id, i64 d) {
    seg[id].val.val += (r - l + 1) * d;
    seg[id].lz.add += d;
}
void down(int l, int r, int id) {
    if (seg[id].lz.add == 0) return;
    auto mid = l + ((r - l) >> 1);
    update(l, mid, mid * 2, seg[id].lz.add);
    update(mid + 1, r, mid * 2 + 1, seg[id].lz.add);
    seg[id].lz.add = 0;
}

void build(int l, int r, int id, const auto &a) {
    if (l == r) {
        seg[id] = {{a[l]}, {}};
    } else {
        auto mid = l + ((r - l) >> 1);
        build(l, mid, mid * 2, a);
        build(mid + 1, r, mid * 2 + 1, a);
        rise(l, r, id);
    }
}

void add(int l, int r, int id, int ml, int mr, i64 d) {
    if (l == ml && r == mr) {
        update(l, r, id, d);
    } else {
        auto mid = l + ((r - l) >> 1);
        down(l, r, id);
        if (mr <= mid) {
            add(l, mid, mid * 2, ml, mr, d);
        } else if (ml > mid) {
            add(mid + 1, r, mid * 2 + 1, ml, mr, d);
        } else {
            add(l, mid, mid * 2, ml, mid, d);
            add(mid + 1, r, mid * 2 + 1, mid + 1, mr, d);
        }
        rise(l, r, id);
    }
}

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + ((r - l) >> 1);
        down(l, r, id);
        if (qr <= mid) {
            return query(l, mid, mid * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, mid * 2 + 1, ql, qr);
        } else {
            return query(l, mid, mid * 2, ql, mid) + query(mid + 1, r, mid * 2 + 1, mid + 1, qr);
        }
    }
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int n, q;
    std::cin >> n >> q;
    
    std::vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++) {
        std::cin >> a[i];
    }

    build(1, n, 1, a);

    for (int t = 0; t < q; t ++) {
        int opt;
        std::cin >> opt;
        if (opt == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            add(1, n, 1, l, r, k);
        } else {
            int l, r;
            std::cin >> l >> r;
            std::cout << query(1, n, 1, l, r).val << '\n';
        }
    }
}