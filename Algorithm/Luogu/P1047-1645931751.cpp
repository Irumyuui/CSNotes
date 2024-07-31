#include <bits/stdc++.h>
using namespace std;

#define all(X) std::begin(X), std::end(X)
#define cauto const auto
#define endn '\n'

using ll = long long;
using LL = __int128_t;

struct Node {
    int cnt;
    bool mk;
    int lc, rc;
};

constexpr int MAXN = 1e6 + 10;

int tot = 1;
Node tree[MAXN << 5];

inline void update(int &root) {
    tree[root].cnt = tree[ tree[root].lc ].cnt + tree[ tree[root].rc ].cnt;
}

inline void mkdown(int &root) {
    if (!tree[root].mk)
        return;
    tree[ tree[root].lc ].cnt = tree[ tree[root].rc ].cnt = 0;
    tree[ tree[root].lc ].mk = tree[ tree[root].rc ].mk = true;
    tree[root].mk = false;
}

void build(int pll, int prr, int root) {
    if (pll == prr) {
        tree[root].cnt = 1;
        tree[root].mk = false;
        return;
    }

    int mid = pll + ((prr - pll) >> 1);

    tree[root].lc = ++ tot;
    build(pll, mid, tree[root].lc);

    tree[root].rc = ++ tot;
    build(mid + 1, prr, tree[root].rc);

    update(root);
}

void change(int sll, int srr, int pll, int prr, int root) {
    if (sll <= pll && srr >= prr) {
        tree[root].cnt = 0;
        tree[root].mk = true;
        return;
    }

    int mid = pll + ((prr - pll) >> 1);
    mkdown(root);
    if (sll <= mid) {
        change(sll, srr, pll, mid, tree[root].lc);
    }
    if (srr > mid) {
        change(sll, srr, mid + 1, prr, tree[root].rc);
    }

    update(root);
}

int query(int sll, int srr, int pll, int prr, int root) {
    if (sll <= pll && srr >= prr) {
        return tree[root].cnt;
    }

    int mid = pll + ((prr - pll) >> 1);
    int lef = 0, rig = 0;
    mkdown(root);
    if (sll <= mid) {
        lef = query(sll, srr, pll, mid, tree[root].lc);
    }
    if (srr > mid) {
        rig = query(sll, srr, mid + 1, prr, tree[root].rc);
    }
    return lef + rig;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n, t;
    cin >> n >> t;

    n ++;

    int root = tot;
    build(1, n, root);

    while (t --) {
        int l, r;
        cin >> l >> r;
        l ++; r ++;
        change(l, r, 1, n, root);
    }

    cout << query(1, n, 1, n, root);

    return 0;
}