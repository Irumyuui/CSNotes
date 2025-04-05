#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

int n, m, modp;
vector<LL>tree, mkAdd, mkMult, num;

void buildTree(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildTree(pll, mid, pos << 1);
    buildTree(mid + 1, prr, (pos << 1) | 1);
    tree[pos] = (tree[pos << 1] + tree[(pos << 1) | 1]) % modp;
}

void downMark(const int &pll, const int &prr, const int &mid, const int &pos){
    int left = pos << 1, right = (pos << 1) | 1;
    tree[left] = (tree[left] * mkMult[pos] + (mid + 1 - pll) * mkAdd[pos]) % modp;
    tree[right] = (tree[right] * mkMult[pos] + (prr - mid) * mkAdd[pos]) % modp;
    mkMult[left] = mkMult[pos] * mkMult[left] % modp;
    mkMult[right] = mkMult[right] * mkMult[pos] % modp;
    mkAdd[left] = (mkAdd[left] * mkMult[pos] + mkAdd[pos]) % modp;
    mkAdd[right] = (mkAdd[right] * mkMult[pos] + mkAdd[pos]) % modp;
    mkMult[pos] = 1;
    mkAdd[pos] = 0;
}

LL getres(const int &sll, const int &srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr)
        return tree[pos];
    int mid = pll + ((prr - pll) >> 1);
    LL res = 0;
    downMark(pll, prr, mid, pos);
    if (sll <= mid)
        res = (res + getres(sll, srr, pll, mid, pos << 1)) % modp;
    if (srr > mid)
        res = (res + getres(sll, srr, mid + 1, prr, (pos << 1) | 1)) % modp;
    return res;
}

void updateAdd(const int &sll, const int &srr, int pll, int prr, int pos, const int &addn){
    if (sll <= pll && srr >= prr){
        tree[pos] = (tree[pos] + (prr - pll + 1) * addn) % modp;
        mkAdd[pos] += addn;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    downMark(pll, prr, mid, pos);
    if (sll <= mid)
        updateAdd(sll, srr, pll, mid, pos << 1, addn);
    if (srr > mid)
        updateAdd(sll, srr, mid + 1, prr, (pos << 1) | 1, addn);
    tree[pos] = (tree[pos << 1] + tree[(pos << 1) | 1]) % modp;
}

void updateMult(const int &sll, const int &srr, int pll, int prr, int pos, const int &multn){
    if (sll <= pll && srr >= prr){
        tree[pos] = (tree[pos] * multn) % modp;
        mkMult[pos] = mkMult[pos] * multn % modp;
        mkAdd[pos] = mkAdd[pos] * multn % modp;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    downMark(pll, prr, mid, pos);
    if (sll <= mid)
        updateMult(sll, srr, pll, mid, pos << 1, multn);
    if (srr > mid)
        updateMult(sll, srr, mid + 1, prr, (pos << 1) | 1, multn);
    tree[pos] = (tree[pos << 1] + tree[(pos << 1) | 1]) % modp;
}

void solve(){
    cin >> n >> modp;
    num = vector<LL>(n + 1);
    tree = mkAdd = vector<LL>(n << 2, 0);
    mkMult = vector<LL>(n << 2, 1);
    for (int i = 1; i <= n; ++ i)
        cin >> num[i];
    buildTree(1, n, 1);
    cin >> m;
    while (m --){
        int c, l, r, x;
        cin >> c >> l >> r;
        if (c == 1){
            cin >> x;
            updateMult(l, r, 1, n, 1, x);
        }else if (c == 2){
            cin >> x;
            updateAdd(l, r, 1, n, 1, x);
        }else{
            cout << getres(l, r, 1, n, 1) % modp << endl;
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio;
    //freopen("in.in", "r", stdin);
    solve();
    return 0;
}