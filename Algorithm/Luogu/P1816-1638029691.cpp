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
typedef vector<LL> vll;

vll tree, num;

void build(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    build(pll, mid, pos << 1); build(mid + 1, prr, (pos << 1) | 1);
    tree[pos] = min(tree[pos << 1], tree[(pos << 1) | 1]);
}

LL getres(const int &sll, const int &srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr)
        return tree[pos];
    int mid = pll + ((prr - pll) >> 1);
    LL left = INFI, right = INFI;
    if (sll <= mid) left = getres(sll, srr, pll, mid, pos << 1);
    if (srr > mid) right = getres(sll, srr, mid + 1, prr, (pos << 1) | 1);
    return min(left, right);
}

void solve(){
    int n, q;
    cin >> n >> q;
    num = vll(n + 1);
    tree = vll(n << 2);
    for (int i = 1; i <= n; ++ i) cin >> num[i];
    build(1, n, 1);
    while (q --){
        int l, r;
        cin >> l >> r;
        cout << getres(l, r, 1, n, 1) << ' ';
    }
}

int main(){
    FAST(); //FREIN("in.in");
    solve();
    return 0;
}