#include <bits/stdc++.h>
using namespace std;

#define all(X) std::begin(X), std::end(X)
#define cauto const auto
#define endn '\n'

using ll = long long;
using LL = __int128_t;

struct Node {
    ll num;
    int lc, rc; 
    // bool mk;s
};

constexpr int MAXN = 1e6 + 10;
Node tree[MAXN << 5];
ll a[MAXN << 5];
int tot = 1;

inline void update(int &root) {
    tree[root].num = tree[tree[root].lc].num + tree[tree[root].rc].num;
}

void build(int pll, int prr, int root) {
    if (pll == prr) {
        tree[root].num = a[pll];
        // tree[root].mk = false;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);

    tree[root].lc = ++ tot;
    tree[root].rc = ++ tot;

    build(pll, mid, tree[root].lc);
    build(mid + 1, prr, tree[root].rc);

    update(root);
}

void sqrtn(int sll, int srr, int pll, int prr, int root) {
    if (pll == prr) {
        if (tree[root].num > 1) {
            tree[root].num = sqrt(tree[root].num);
        }

        return;
    }
    if (sll <= pll && srr >= prr) {
        if (tree[root].num != (prr - pll + 1)) {
            int mid = pll + ((prr - pll) >> 1);
            if (tree[tree[root].lc].num > (mid - pll + 1)) {
                sqrtn(sll, srr, pll, mid, tree[root].lc);
            }
            if (tree[tree[root].rc].num > (prr - mid)) {
                sqrtn(sll, srr, mid + 1, prr, tree[root].rc);
            }
            update(root);
        }
        return ;
    }

    int mid = pll + ((prr - pll) >> 1);
    if (sll <= mid) {
        sqrtn(sll, srr, pll, mid, tree[root].lc);
    }
    if (srr > mid) {
        sqrtn(sll, srr, mid + 1, prr, tree[root].rc);
    }

    update(root);
}

ll query(int sll, int srr, int pll, int prr, int root) {
    if (sll <= pll && srr >= prr) {
        return tree[root].num;
    }

    int mid = pll + ((prr - pll) >> 1);
    ll res = 0;
    if (sll <= mid) {
        res += query(sll, srr, pll, mid, tree[root].lc);
    }
    if (srr > mid) {
        res += query(sll, srr, mid + 1, prr, tree[root].rc);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++ i) cin >> a[i];

    int root = tot;
    build(1, n, root);

    int t;
    cin >> t;
    while (t --) {
        int opt, l ,r;
        cin >> opt >> l >> r;
        
        if (l > r) {
            swap(l, r);
        }

        if (opt == 0) {
            sqrtn(l, r, 1, n, root);
        } else {
            cout << query(l, r, 1, n, root) << '\n';
            // cout << '\n';
        }
        // cout << '\n';
    }

    return 0;
}