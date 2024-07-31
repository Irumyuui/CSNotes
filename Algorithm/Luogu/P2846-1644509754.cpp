#include <bits/stdc++.h>
using namespace std;

const int N = 1e7 + 10;
int tr[N << 2];
int mk[N << 2];

inline void pushdown(int pll, int mid, int prr, int pos){
    if (!mk[pos]){
        return;
    }

    tr[pos << 1] = (mid - pll + 1) - tr[pos << 1];
    tr[(pos << 1) | 1] = (prr - mid) - tr[(pos << 1) | 1];

    mk[pos << 1] ^= 1;
    mk[(pos << 1) | 1] ^= 1;

    mk[pos] = 0;
}

void update(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && prr <= srr){
        tr[pos] = (prr - pll + 1) - tr[pos];
        mk[pos] ^= 1;
        return;
    }

    int mid = pll + ((prr - pll) >> 1);

    pushdown(pll, mid, prr, pos);

    if (sll <= mid){
        update(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        update(sll, srr, mid + 1, prr, (pos << 1) | 1);
    }

    tr[pos] = tr[pos << 1] + tr[(pos << 1) | 1];
}

int querysum(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        return tr[pos];
    }

    int mid = pll + ((prr - pll) >> 1);

    pushdown(pll, mid, prr, pos);

    int res = 0;
    if (sll <= mid){
        res += querysum(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        res += querysum(sll, srr, mid + 1, prr, (pos << 1) | 1);
    }

    return res;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int len, t;
    cin >> len >> t;

    while (t --){
        int c, l, r;
        cin >> c >> l >> r;

        if (c == 0){
            update(l, r, 1, len, 1);
        }else{
            cout << querysum(l, r, 1, len, 1) << '\n';
        }
    }

    return 0;
}