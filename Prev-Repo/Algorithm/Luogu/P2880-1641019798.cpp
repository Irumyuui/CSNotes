#include <bits/stdc++.h>
#define endn "\n"
using namespace std;
typedef long long LL;
typedef pair<int, int> PII;

const int LEN = 2e5 + 115;
LL n, q, ll, rr;
LL maxt[LEN << 2], mint[LEN << 2], arr[LEN];

void buildmaxt(int pll, int prr, int pos){
    if (pll == prr){
        maxt[pos] = arr[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildmaxt(pll, mid, pos << 1);
    buildmaxt(mid + 1, prr, (pos << 1) | 1);
    maxt[pos] = max(maxt[pos << 1], maxt[(pos << 1) | 1]);
}

void buildmint(int pll, int prr, int pos){
    if (pll == prr){
        mint[pos] = arr[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildmint(pll, mid, pos << 1);
    buildmint(mid + 1, prr, (pos << 1) | 1);
    mint[pos] = min(mint[pos << 1], mint[(pos << 1) | 1]);
}

LL querymax(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        return maxt[pos];
    }
    int mid = pll + ((prr - pll) >> 1);
    LL res = -0x7fffffffffff;
    if (sll <= mid){
        res = querymax(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        res = max(res, querymax(sll, srr, mid + 1, prr, (pos << 1) | 1));
    }
    return res;
}

LL querymin(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        return mint[pos];
    }
    int mid = pll + ((prr - pll) >> 1);
    LL res = 0x7fffffffffff;
    if (sll <= mid){
        res = querymin(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        res = min(querymin(sll, srr, mid + 1, prr, (pos << 1) | 1), res);
    }
    return res;
}


void solve(){
    fill(maxt, maxt + (LEN << 2), -0x7fffffffff);
    fill(mint, mint + (LEN << 2), 0x7fffffffff);
    cin >> n >> q;
    for (int i = 1; i <= n; ++ i){
        cin >> arr[i];
    }
    buildmaxt(1, n, 1);
    buildmint(1, n, 1);
    while (q --){
        cin >> ll >> rr;
        cout << querymax(ll, rr, 1, n, 1) - querymin(ll, rr, 1, n, 1) << endn;
    }
}

int main(){
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
#endif
    std::ios::sync_with_stdio(false);
    solve();
    return 0;
}