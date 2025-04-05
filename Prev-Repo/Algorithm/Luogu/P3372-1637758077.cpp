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

int n, q;
vector<LL>num, d, mark;

inline void read(){
    cin >> n >> q;
    num = vector<LL>(n + 1);
    d = mark = vector<LL>(4 * n, 0);
    for (int i = 1; i <= n; ++ i) cin >> num[i];
}

void buildTree(int pll, int prr, int pos){
    if (pll == prr){
        d[pos] = num[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    buildTree(pll, mid, pos << 1);
    buildTree(mid + 1, prr, (pos << 1) + 1);
    d[pos] = d[pos << 1] + d[(pos << 1) + 1];
}

void downMark(const int &pos, const int &mid, const int &pll, const int &prr){
    d[pos << 1] += (mid + 1 - pll) * mark[pos];
    mark[pos << 1] += mark[pos];
    d[(pos << 1) + 1] += (prr - mid) * mark[pos];
    mark[(pos << 1) + 1] += mark[pos];
    mark[pos] = 0;
}

LL getSumAdd(int sll, int srr, int pll, int prr, int pos){
    if (sll <= pll && srr >= prr){
        return d[pos];
    }
    int mid = pll + ((prr - pll) >> 1);
    LL sum = 0;
    if (mark[pos]){
        downMark(pos, mid, pll, prr);
    }
    if (sll <= mid){
        sum += getSumAdd(sll, srr, pll, mid, (pos << 1));
    }
    if (srr > mid){
        sum += getSumAdd(sll, srr, mid + 1, prr, (pos << 1) + 1);
    }
    return sum;
}

void upDateAdd(int sll, int srr, int pll, int prr, int pos, int change){
    if (sll <= pll && srr >= prr){
        d[pos] += (prr - pll + 1) * change;
        mark[pos] += change;
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    if (mark[pos] && pll != prr){
        downMark(pos, mid, pll, prr);
    }
    if (sll <= mid){
        upDateAdd(sll, srr, pll, mid, (pos << 1), change);
    }
    if (srr > mid){
        upDateAdd(sll, srr, mid + 1, prr, (pos << 1) + 1, change);
    }
    d[pos] = d[pos << 1] + d[(pos << 1) + 1];
}

void solve(){
    read();
    buildTree(1, n, 1);
    while (q --){
        int com, ll, rr, x;
        cin >> com >> ll >> rr;
        if (com == 1){
            cin >> x;
            upDateAdd(ll, rr, 1, n, 1, x);
        }else{
            cout << getSumAdd(ll, rr, 1, n, 1) << endl;
        }
    }
    return;
}

int main(){
    FAST();
    //FREIN("in.in");
    solve();
    return 0;
}