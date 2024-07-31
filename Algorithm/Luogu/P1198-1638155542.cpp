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

LL modp;
const LL LEN = 2e6 + 10;
LL tree[LEN];

void update(LL pll, LL prr, LL pos, LL k, LL kpos){
    if (pll == prr){
        tree[pos] = k;
        return;
    }
    LL mid = pll + ((prr - pll) >> 1);
    if (kpos <= mid) update(pll, mid, pos << 1, k, kpos);
    else if (kpos > mid) update(mid + 1, prr, (pos << 1) | 1, k, kpos);
    tree[pos] = max(tree[pos << 1], tree[(pos << 1) | 1]) % modp;
}

LL getres(LL sll, LL srr, LL pll, LL prr, LL pos){
    if (sll <= pll && srr >= prr) return tree[pos];
    LL mid = pll + ((prr - pll) >> 1);
    LL left, right;
    left = right = -2e9;
    if (sll <= mid) left = getres(sll, srr, pll, mid, pos << 1);
    if (srr > mid) right = getres(sll, srr, mid + 1, prr, (pos << 1) | 1);
    return max(left, right) % modp;
}

void solve(){
    LL m, bef = 0, len = 0;
    cin >> m >> modp;
    for (int i = 1; i <= m; ++ i){
        char c;
        LL k;
        cin >> c >> k;
        if (c == 'A'){
            update(1, m, 1, (k + bef) % modp, ++ len);
        }else{
            cout << (bef = getres(len - k + 1, len, 1, m, 1)) << endl;
        }
    }
}

int main(){
    FAST(); //FREIN("in.in");
    fill(tree, tree + LEN, LL(-2e9));
    solve();
    return 0;
}