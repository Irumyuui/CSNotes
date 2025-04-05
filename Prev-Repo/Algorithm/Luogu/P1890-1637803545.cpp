#include <bits/stdc++.h>

#define debug(X) std::cerr << #X << ' : ' << X << std::endl
#define FAST() std::ios::sync_with_stdio(false)
#define VALNAME(X) (#X)

inline void FREIN(const char *text){
    freopen(text, "r", stdin);
}

template<class Type> inline void ddebug(const Type X){
    std::cerr << "debug : " << X << std::endl;
}

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<long long, long long> PLL;

inline int gcd(int a, int b){
    if (a == 0) return b;
    else if (b == 0) return a;
    while (b ^= a ^= b ^= a %= b);
    return a;
}

vector<int>tree, num;

void buildTree(int pll, int prr, int pos){
    if (pll == prr){
        tree[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildTree(pll, mid, pos << 1);
    buildTree(mid + 1, prr, (pos << 1) + 1);
    tree[pos] = gcd(tree[pos << 1], tree[(pos << 1) + 1]);
}

int getGCD(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr)
        return tree[pos];
    int mid = pll + ((prr - pll) >> 1), t = 0;
    if (sll <= mid)
        t = getGCD(sll, srr, pll, mid, pos << 1);
    if (srr > mid)
        t = gcd(t, getGCD(sll, srr, mid + 1, prr, (pos << 1) + 1));
    return t;
}

void solve(){
    int n, m;
    cin >> n >> m;
    tree = vector<int>(4 * n);
    num = vector<int>(n);
    for (int i = 1; i <= n; ++ i)
        cin >> num[i];
    buildTree(1, n, 1);
    while (m --){
        int ll, rr;
        cin >> ll >> rr;
        cout << getGCD(ll, rr, 1, n, 1) << endl;
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}