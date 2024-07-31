#include<bits/stdc++.h>
using namespace std;

int n;
vector<int>tree, num;

inline void upTree(int pos){
    tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
}

void buildtree(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildtree(pll, mid, pos << 1); buildtree(mid + 1, prr, (pos << 1) | 1);
    upTree(pos);
}

void singleAdd(int target, int k, int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] += k;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    if (target <= mid) singleAdd(target, k, pll, mid, pos << 1);
    else singleAdd(target, k, mid + 1, prr, (pos << 1) | 1);
    upTree(pos);
}

int getres(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && prr <= srr) return tree[pos];
    int mid = pll + ((prr - pll) >> 1), res = 0;
    if (sll <= mid) res += getres(sll, srr, pll, mid, pos << 1);
    if (srr > mid) res += getres(sll, srr, mid + 1, prr, (pos << 1) | 1);
    return res;
}

int x, a, b;
void solve(){
    cin >> x >> a >> b;
    if (x == 1){
        singleAdd(a, b, 1, n, 1);
    }else{
        cout << getres(a, b, 1, n, 1) << endl;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    int m;
    cin >> n >> m;
    tree = vector<int>(n << 2, 0);
    num = vector<int>(n + 1, 0);
    for (int i = 1; i <= n; ++ i) cin >> num[i];
    buildtree(1, n, 1);
    while (m --){
        solve();
    }
    return 0;
}