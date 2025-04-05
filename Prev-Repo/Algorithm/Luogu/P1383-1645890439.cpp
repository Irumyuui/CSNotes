#include <bits/stdc++.h>
using namespace std;

#define all(X) std::begin(X), std::end(X)
#define cauto const auto
#define endn '\n'

using ll = long long;
using LL = __int128_t;

struct Node {
    char val;
    int lc, rc;
    int len;
    // Node(char val = 0, int lc = 0, int rc = 0) : val(val), lc(lc), rc(rc){}
};

constexpr int MAXN = 1e6 + 10;
Node tree[MAXN << 5];
int ver[MAXN];

int tot = 1;

void build(int pll, int prr, int pos) {
    if (pll == prr) {
        tree[pos].val = 0;
        tree[pos].len = 0;
        return;
    }

    int mid = pll + ((prr - pll) >> 1);
    tree[pos].lc = ++ tot;
    build(pll, mid, tree[pos].lc);
    tree[pos].rc = ++ tot;
    build(mid + 1, prr, tree[pos].rc);
}

void type(int addpos, char val, int pll, int prr, int op, int np) {
    if (pll == prr) {
        tree[np].val = val;
        tree[np].len ++;
        return;
    }

    tree[np].lc = tree[op].lc;
    tree[np].rc = tree[op].rc;

    int mid = pll + ((prr - pll) >> 1);

    if (addpos <= mid) {
        tree[np].lc = ++ tot;
        type(addpos, val, pll, mid, tree[op].lc, tree[np].lc);
    } else {
        tree[np].rc = ++ tot;
        type(addpos, val, mid + 1, prr, tree[op].rc, tree[np].rc);
    }

    tree[np].len = tree[ tree[np].lc ].len + tree[ tree[np].rc ].len;
}

char query(int quepos, int pll, int prr, int verpos) {
    if (pll == prr) {
        return tree[verpos].val;
    }
    int mid = pll + ((prr - pll) >> 1);
    if (quepos <= mid) {
        return query(quepos, pll, mid, tree[verpos].lc);
    } else {
        return query(quepos, mid + 1, prr, tree[verpos].rc);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    ver[0] = 1;
    build(1, n, ver[0]);

    int nowlen = 0, dat = 0;
    for (int i = 1; i <= n; ++ i) {
        char opt;
        cin >> opt;

        if (opt == 'T') {
            char x;
            cin >> x;
            ver[++ dat] = ++ tot;
            type(++ nowlen, x, 1, n, ver[dat - 1], ver[dat]);
        } else if (opt == 'U') {
            int x;
            cin >> x;
            ver[dat + 1] = ver[dat - x];
            nowlen = tree[ ver[dat - x] ].len;
            dat ++;
        } else {
            int x;
            cin >> x;
            cout << query(x, 1, n, ver[dat]) << '\n';
        }
    }

    return 0;
}