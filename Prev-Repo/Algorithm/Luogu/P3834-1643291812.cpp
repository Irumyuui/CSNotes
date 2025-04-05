#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

const int N = 2e5 + 10;
struct node
{
    int val, lc, rc;
}tree[N << 5];
int a[N], b[N], roots[N], cnt = 1;

void build(int pll, int prr, int pos)
{
    if (pll == prr)return;
    tree[pos].lc = ++ cnt;
    tree[pos].rc = ++ cnt;
    int mid = (pll + prr) >> 1;
    build(pll, mid, tree[pos].lc); build(mid + 1, prr, tree[pos].rc);
}

void update(int x, int pll, int prr, int opos, int npos)
{
    if (pll == prr){
        tree[npos].val = tree[opos].val + 1;
        return;
    }
    tree[npos].lc = tree[opos].lc;
    tree[npos].rc = tree[opos].rc;
    int mid = (pll + prr) >> 1;
    if (x <= mid){
        tree[npos].lc = ++ cnt;
        update(x, pll, mid, tree[opos].lc, tree[npos].lc);
    }else{
        tree[npos].rc = ++ cnt;
        update(x, mid + 1, prr, tree[opos].rc, tree[npos].rc);
    }
    tree[npos].val = tree[tree[npos].lc].val + tree[tree[npos].rc].val;
}

int query(int pll, int prr, int lp, int rp, int k)
{
    if (pll == prr){
        return pll;
    }
    int x = tree[tree[rp].lc].val - tree[tree[lp].lc].val, mid = (pll + prr) >> 1;
    if (x >= k){
        return query(pll, mid,tree[lp].lc, tree[rp].lc, k);
    }else{
        return query(mid + 1, prr, tree[lp].rc, tree[rp].rc, k - x);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, t;
    cin >> n >> t;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> a[i];
        b[i] = a[i];
    }
    sort(b + 1, b + 1 + n);
    int len = unique(b + 1, b + 1 + n) - b - 1;
    build(1, len, 1);
    roots[0] = 1;
    for (int i = 1; i <= n; ++ i)
    {
        a[i] = lower_bound(b + 1, b + 1 + len, a[i]) - b;
        roots[i] = ++ cnt;
        update(a[i], 1, len, roots[i - 1], roots[i]);
    }
    while (t --)
    {
        int l, r, k;
        cin >> l >> r >> k;
        cout << b[query(1, len, roots[l - 1], roots[r], k)] << '\n';
    }
    return 0;
}