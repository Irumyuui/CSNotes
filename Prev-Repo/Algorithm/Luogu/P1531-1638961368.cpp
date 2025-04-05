#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;

vector<int>tree, point;

void buildTree(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = point[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildTree(pll, mid, pos << 1);
    buildTree(mid + 1, prr, (pos << 1) | 1);
    tree[pos] = max(tree[pos << 1], tree[(pos << 1) | 1]);
}

int getres(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && prr <= srr) return tree[pos];
    int mid = pll + ((prr - pll) >> 1), res = -INFI;
    if (sll <= mid) res = max(res, getres(sll, srr, pll, mid, pos << 1));
    if (srr > mid) res = max(res, getres(sll, srr, mid + 1, prr, (pos << 1) | 1));
    return res;
}

void singleUpdate(int pll, int prr, int pos, int target, int k){
    if (pll == prr){
        tree[pos] = max(tree[pos], k);
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    if (target <= mid) singleUpdate(pll, mid, pos << 1, target, k);
    else singleUpdate(mid + 1, prr, (pos << 1) | 1, target, k);
    tree[pos] = max(tree[pos << 1], tree[(pos << 1) | 1]);
}

void solve(){
    int n, m;
    cin >> n >> m;
    tree = vector<int>(n << 2, -INFI);
    point = vector<int>(n + 1);
    for (int i = 1; i <= n; ++ i) cin >> point[i];
    buildTree(1, n, 1);
    while (m --){
        char x;
        int a, b;
        cin >> x >> a >> b;
        if (x == 'Q'){
            cout << getres(a, b, 1, n, 1) << endl;
        }else{
            singleUpdate(1, n, 1, a, b);
        }
    }
}

int main(){
    FAST(); 
    //FREIN("in.in");
    solve();
    return 0;
}