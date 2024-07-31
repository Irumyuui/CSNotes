#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

const int N = 1e6 + 10;

struct node
{
    int val, lc, rc;
}tree[N << 5];

int arr[N], roots[N], cnt = 1;

void build(int pll, int prr, int pos)
{
    if (pll == prr){
        tree[pos].val = arr[pll];
        return;
    }
    tree[pos].lc = ++ cnt;
    tree[pos].rc = ++ cnt;
    int mid = (pll + prr) >> 1;
    build(pll, mid, tree[pos].lc);
    build(mid + 1, prr, tree[pos].rc);
    tree[pos].val = tree[tree[pos].lc].val + tree[tree[pos].rc].val;
}

void update(int x, int val, int pll, int prr, int opos, int npos)
{
    if (pll == prr){
        tree[npos].val = val;
        return;
    }
    tree[npos].lc = tree[opos].lc;
    tree[npos].rc = tree[opos].rc;
    int mid = (pll + prr) >> 1;
    if (x <= mid){
        tree[npos].lc = ++ cnt;
        update(x, val, pll, mid, tree[opos].lc, tree[npos].lc);
    }else{
        tree[npos].rc = ++ cnt;
        update(x, val, mid + 1, prr, tree[opos].rc, tree[npos].rc);
    }
    tree[npos].val = tree[tree[npos].lc].val + tree[tree[npos].rc].val;
}

int query(int x, int pll, int prr, int vpos)
{
    if (pll == prr){
        return tree[vpos].val ;
    }
    int mid = (pll + prr) >> 1;
    if (x <= mid){
        return query(x, pll, mid, tree[vpos].lc);
    }else{
        return query(x, mid + 1, prr, tree[vpos].rc);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> arr[i];
    }
    build(1, n, 1);
    roots[0] = 1;
    for (int i = 1; i <= m; ++ i)
    {
        int ver, com, x;
        cin >> ver >> com;
        if (com == 1){
            int val;
            roots[i] = ++ cnt;
            cin >> x >> val;
            update(x, val, 1, n, roots[ver], roots[i]);
        }else{
            cin >> x;
            roots[i] = roots[ver];
            cout << query(x, 1, n, roots[i]) << '\n';
        }
    }
    return 0;
}