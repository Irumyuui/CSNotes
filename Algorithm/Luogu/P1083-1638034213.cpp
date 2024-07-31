#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
#define debug(X) std::cerr << #X << ' : ' << X << std::endl
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

vector<LL> tree, num, mk;

void build(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    build(pll, mid, pos << 1);
    build(mid + 1, prr, (pos << 1) | 1);
    tree[pos] = min(tree[pos << 1], tree[(pos << 1) | 1]);
}

void downMark(int pos, int pll, int prr, int mid){
    tree[pos << 1] -= mk[pos];
    tree[(pos << 1) | 1] -= mk[pos];
    mk[pos << 1] += mk[pos];
    mk[(pos << 1) | 1] += mk[pos];
    mk[pos] = 0;
}

LL getres(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr) return tree[pos];
    int mid = pll + ((prr - pll) >> 1);
    LL l = INFI, r = INFI;
    downMark(pos, pll, prr, mid);
    if (sll <= mid) l = getres(sll, srr, pll, mid, pos << 1);
    if (srr > mid) r = getres(sll, srr, mid + 1, prr, (pos << 1) | 1);
    return min(l, r);
}

void update(int sll, int srr, int pll, int prr, int pos, LL x){
    if (sll <= pll && srr >= prr){
        tree[pos] -= x;
        mk[pos] += x;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    downMark(pos, pll, prr, mid);
    if (sll <= mid) update(sll, srr, pll, mid, pos << 1, x);
    if (srr > mid) update(sll, srr, mid + 1, prr, (pos << 1) | 1, x);
    tree[pos] = min(tree[pos << 1], tree[(pos << 1) | 1]);
}

void solve(){
    int n, q;
    cin >> n >> q;
    num = vector<LL>(n + 1);
    tree = vector<LL>(n << 2, INFI);
    mk = vector<LL>(n << 2, 0);
    for (int i = 1; i <= n; ++ i) cin >> num[i];
    build(1, n, 1);
    for (int i = 1; i <= q; ++ i){
        LL k;
        int l, r;
        cin >> k >> l >> r;
        if (k <= getres(l, r, 1, n, 1)){
            update(l, r, 1, n, 1, k);
        }else{
            cout << "-1" << endl << i << endl;
            return;
        }
    }
    cout << "0" << endl;
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}