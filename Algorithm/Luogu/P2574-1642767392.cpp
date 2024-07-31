#include <bits/stdc++.h>

using namespace std;

const int LEN = 2e5 + 10;
int arr[LEN], tree[LEN << 2];
bool tag[LEN << 2];

void build(int pll, int prr, int pos)
{
    if (pll == prr){
        tree[pos] = arr[pll];
        return;
    }
    int mid = pll + ((prr - pll) >> 1);
    build(pll, mid, pos << 1);
    build(mid + 1, prr, (pos << 1) | 1);
    tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
}

void down(int pll, int prr, int pos)
{
    if (!tag[pos])
        return;
    int mid = pll + ((prr - pll) >> 1);
    tree[pos << 1] = (mid - pll + 1) - tree[pos << 1];
    tree[(pos << 1) | 1] = (prr - mid) - tree[(pos << 1) | 1];
    tag[pos << 1] ^= 1;
    tag[(pos << 1) | 1] ^= 1;
    tag[pos] = 0;
}

int query(int sll, int srr, int pll, int prr, int pos)
{
    if (sll <= pll && srr >= prr){
        return tree[pos];
    }
    down(pll, prr, pos);
    int mid = pll + ((prr - pll) >> 1), res = 0;
    if (sll <= mid){
        res += query(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        res += query(sll, srr, mid + 1, prr, (pos << 1) | 1);
    }
    return res;
}

void XOR(int sll, int srr, int pll, int prr, int pos)
{
    if (sll <= pll && srr >= prr){
        tree[pos] = (prr - pll + 1) - tree[pos];
        tag[pos] ^= 1;
        return;
    }
    down(pll, prr, pos);
    int mid = pll + ((prr - pll) >> 1);
    if (sll <= mid){
        XOR(sll, srr, pll, mid, pos << 1);
    }
    if (srr > mid){
        XOR(sll, srr, mid + 1, prr, (pos << 1) | 1);
    }
    tree[pos] = tree[pos << 1] + tree[(pos << 1) | 1];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
    {
        char c;
        cin >> c;
        arr[i] = c == '1';
    }
    build(1, n, 1);
    while (m --)
    {
        int x, ll, rr;
        cin >> x >> ll >> rr;
        if (x == 0){
            XOR(ll, rr, 1, n, 1);
        }else{
            cout << query(ll, rr, 1, n, 1) << '\n';
        }
    }
    return 0;
}