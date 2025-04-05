#include <bits/stdc++.h>

#if !defined (ONLINE_JUDGE)
#  include "./include/debug.hpp"
#else
#  define debug(...)
#endif

using i64 = int64_t;

constexpr int N = 2e5 + 10;

struct Node {
    struct Info {
        i64 val;
        Info(i64 val = 0) : val(val) {}
        friend Info operator + (const Info &left, const Info &right) {
            return Info {left.val + right.val};
        }
    };
    struct Lazy {
        i64 add;
        Lazy(i64 add = 0) : add(add) {}
        bool Have() const {
            return add != 0;
        }
        void Clear() {
            add = 0;
        }
    };

    Info val;
    Lazy lz;
};

using Info = Node::Info;
using Lazy = Node::Lazy;

std::vector<Node> seg;

void init(int n) {
    seg.resize(n * 4 + 10);
}

__always_inline void rise(int id) {
    seg[id].val = seg[id * 2].val + seg[id * 2 + 1].val;
}

__always_inline void update(int l, int r, int id, const Lazy &lz) {
    seg[id].val.val += (r - l + 1) * lz.add;
    seg[id].lz.add += lz.add;
}

__always_inline void down(int l, int r, int id) {
    if (auto &lz = seg[id].lz; lz.Have()) {
        auto mid = l + (r - l) / 2;
        update(l, mid, id * 2, lz);
        update(mid + 1, r, id * 2 + 1, lz);
        lz.Clear();
    }
}

void build(int l, int r, int id, const auto &seq) {
    debug(l, r, id);
    seg[id].lz.Clear();
    if (l == r) {
        seg[id].val.val = seq[l];
    } else {
        auto mid = l + (r - l) / 2;
        build(l, mid, id * 2, seq);
        build(mid + 1, r, id * 2 + 1, seq);
        rise(id);
    }
}

void apply(int l, int r, int id, int ml, int mr, const Lazy &lz) {
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

Info query(int l, int r, int id, int ql, int qr) {
    if (l == ql && r == qr) {
        return seg[id].val;
    } else {
        auto mid = l + (r - l) / 2;
        down(l, r, id);
        if (qr <= mid) {
            return query(l, mid, id * 2, ql, qr);
        } else if (ql > mid) {
            return query(mid + 1, r, id * 2 + 1, ql, qr);
        } else {
            return query(l, mid, id * 2, ql, mid) + query(mid + 1, r, id * 2 + 1, mid + 1, qr);
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;

    debug(n, q);

    std::vector<i64> a(n);
    for (int i = 0; i < n; i += 1) {
        std::cin >> a[i];
    }
    for (int i = n - 1; i >= 1; i -= 1) {
        a[i] -= a[i - 1];
    }

    init(n);
    debug(0, n - 1);
    build(0, n - 1, 1, a);

    for (int t = 0; t < q; t += 1) {
        int opt;
        std::cin >> opt;

        if (opt == 1) {
            int l, r;
            i64 k, d;
            std::cin >> l >> r >> k >> d;
            l -= 1; r -= 1;

            apply(0, n - 1, 1, l, l, Lazy{k});
            if (l + 1 <= r) {
                apply(0, n - 1, 1, l + 1, r, Lazy{d});            
            }
            if (r + 1 < n) {
                apply(0, n - 1, 1, r + 1, r + 1, Lazy{-(k + (r - l) * d)});
            }
        } else {
            int p;
            std::cin >> p;
            p -= 1;
            auto ret = query(0, n - 1, 1, 0, p);
            std::cout << ret.val << '\n';
        }
    }
}