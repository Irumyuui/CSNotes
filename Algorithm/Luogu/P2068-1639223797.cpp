#include <bits/stdc++.h>
#define FAST() std::ios::sync_with_stdio(false)
inline void FREIN(const char *text){freopen(text, "r", stdin);}
using namespace std;
const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

int n, m;
vector<LL>tree, mk;

inline void downmk(int pll, int prr, int mid, int pos){
    if (!mk[pos]) return;
    tree[pos << 1] += mk[pos] * (mid - pll + 1);
    tree[(pos << 1) | 1] += mk[pos] * (prr - mid);
    mk[pos << 1] += mk[pos];
    mk[(pos << 1) | 1] += mk[pos];
    mk[pos] = 0;
}

LL query(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr) return tree[pos];
    int mid = pll + ((prr - pll) >> 1);
    LL res = 0;
    downmk(pll, prr, mid, pos);
    if (sll <= mid) res += query(sll, srr, pll, mid, pos << 1);
    if (srr > mid) res += query(sll, srr, mid + 1, prr, (pos << 1) | 1);
    return res;
}

void singleAdd(int target, int k, int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] += k;
        mk[pos] += k;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    downmk(pll, prr, mid, pos);
    if (target <= mid) singleAdd(target, k, pll, mid, pos << 1);
    else singleAdd(target, k, mid + 1, prr, (pos << 1) | 1);
    tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
}

void solve(){
    char c;
    LL a, b;
    cin >> c >> a >> b;
    if (c == 'x'){
        singleAdd(a, b, 1, n, 1);
    }else{
        cout << query(a, b, 1, n, 1) << endl;
    }
}

int main(){
    FAST(); 
    //FREIN("in.in");
    cin >> n >> m;
    tree = mk = vector<LL>(n << 2, 0);
    while (m --)
        solve();
    return 0;
}