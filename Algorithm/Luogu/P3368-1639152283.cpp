#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

int n, m;
vector<LL>tree, num, mk;

inline void update(int pos){
    tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
}

void buildtree(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildtree(pll, mid, pos << 1);
    buildtree(mid + 1, prr, (pos << 1) | 1);
    update(pos);
}

inline void downmk(int pll, int prr, int mid, int pos){
    mk[pos << 1] += mk[pos];
    mk[(pos << 1) | 1] += mk[pos];
    tree[pos << 1] += (mid - pll + 1) * mk[pos];
    tree[(pos << 1) | 1] += (prr - mid) * mk[pos];
    mk[pos] = 0;
}

LL query(int target, int pll, int prr, int pos){
    if (pll == prr) return tree[pos];
    int mid = pll + ((prr - pll) >> 1);
    downmk(pll, prr, mid, pos);
    if (target <= mid) return query(target, pll, mid, pos << 1);
    else return query(target, mid + 1, prr, (pos << 1) | 1);
}

void Add(int sll, int srr, LL mka, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        mk[pos] += mka;
        tree[pos] += (prr - pll + 1) * mka;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    downmk(pll, prr, mid, pos);
    if (sll <= mid) Add(sll, srr, mka, pll, mid, pos << 1);
    if (srr > mid) Add(sll, srr, mka, mid + 1, prr, (pos << 1) | 1);
    update(pos);
}

void solve(){
    LL c, x, y, k;
    cin >> c;
    if (c == 1){
        cin >> x >> y >> k;
        Add(x, y, k, 1, n, 1);
    }else{
        cin >> x;
        cout << query(x, 1, n, 1) << endl;
    }
}

int main(){
    std::ios::sync_with_stdio(false);
    //freopen("in.in", "r", stdin);
    cin >> n >> m;
    tree = mk = vector<LL>(n << 2, 0);
    num = vector<LL>(n + 1);
    for (int i = 1; i <= n; ++ i) cin >> num[i];
    buildtree(1, n, 1);
    while (m --){
        solve();
    }
    return 0;
}