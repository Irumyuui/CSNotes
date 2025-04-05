#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << " " << x << '\n' 

class Seg {
    private:
        struct Node {
            int val;
            int lc, rc;
            Node() {
                val = lc = rc = 0;
            }
        };
        int tot, n;
        std::vector<Node> tr;
        void update(int now) {
            tr[now].val = std::__gcd(tr[tr[now].lc].val, tr[tr[now].rc].val); 
        }
        void build(int l, int r, int now, std::vector<int> & a) {
            if (l == r) {
                tr[now].val = a[l];
                return;
            }
            int mid = l + r >> 1;
            tr[now].lc = ++ tot;
            build(l, mid, tr[now].lc, a);
            tr[now].rc = ++ tot;
            build(mid + 1, r, tr[now].rc, a);
            update(now);
        }
        int query(int sl, int sr, int l, int r, int now) {
            if (sl <= l && sr >= r) 
                return tr[now].val;
            int mid = l + r >> 1;
            int d = 0;
            if (sl <= mid)
                d = query(sl, sr, l, mid, tr[now].lc);
            if (sr > mid) 
                d = std::__gcd(d, query(sl, sr, mid + 1, r, tr[now].rc));
            return d;
        }
    public:
        void init(int size, std::vector<int> & a) {
            tot = 1;
            n = size;
            tr.assign(n << 3, Node());
            build(1, n, 1, a);
        }
        auto query(int l, int r) {
            return query(l, r, 1, n, 1);
        }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, t;
    std::cin >> n >> t;
    
    std::vector<int> v(n + 1);
    for (int i = 1; i <= n; ++ i)
        std::cin >> v[i];
    Seg tr;
    tr.init(n, v);

    while (t --) {
        int l, r;
        std::cin >> l >> r;
        std::cout << tr.query(l, r) << '\n';
    }

    return 0;
}