#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;

const int LEN = 1e5 + 115;
LL tree[LEN << 2], q, MOD;

void signlec(int kpos, int k, int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = k;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    if (kpos <= mid){
        signlec(kpos, k, pll, mid, pos << 1);
    }else{
        signlec(kpos, k, mid + 1, prr, (pos << 1) | 1);
    }
    tree[pos] = (tree[pos << 1] * tree[(pos << 1) | 1]) % MOD;
}

LL query(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        return tree[pos];
    }
    int mid = pll + ((prr - pll) >> 1);
    LL left, right;
    left = right = 1;
    if (sll <= mid){
        left = query(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        right = query(sll, srr, mid + 1, prr, (pos << 1) | 1);
    }
    return (left * right) % MOD;
}

void solve(){
    cin >> q >> MOD;
    fill(tree, tree + (LEN << 2), 1);
    for (int i = 1; i <= q; ++ i){
        LL c, j;
        cin >> c >> j;
        if (c == 1){
            signlec(i, j, 1, q, 1);
        }else{
            signlec(j, 1, 1, q, 1);
        }
        cout << query(1, q, 1, q, 1) << endn;
    }
}

int t;
int main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in", "r", stdin);
    #endif
    cin >> t;
    while (t --){
        solve();
    }
    return 0;
}