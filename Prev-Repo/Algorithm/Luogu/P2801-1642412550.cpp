#include <bits/stdc++.h>

using namespace std;

const int LEN = 1e6 + 10;
int L[LEN], R[LEN], arr[LEN], marr[LEN], sum[LEN], belong[LEN], mk[LEN];
int n, tot;

void add(int sll, int srr, int k)
{
    int pll = belong[sll], prr = belong[srr];
    if (pll == prr){
        for (int i = sll; i <= srr; ++ i)
        {
            arr[i] += k;
        }
        for (int i = L[pll]; i <= R[prr]; ++ i)
        {
            marr[i] = arr[i];
        }
        sort(marr + L[pll], marr + R[prr] + 1);
        return;
    }
    for (int i = pll + 1; i < prr; ++ i)
    {
        mk[i] += k;
    }
    for (int i = sll; i <= R[pll]; ++ i)
    {
        arr[i] += k;
    }
    for (int i = L[pll]; i <= R[pll]; ++ i)
    {
        marr[i] = arr[i];
    }
    sort(marr + L[pll], marr + R[pll] + 1);
    for (int i = L[prr]; i <= srr; ++ i)
    {
        arr[i] += k;
    }
    for (int i = L[prr]; i <= R[prr]; ++ i)
    {
        marr[i] = arr[i];
    }
    sort(marr + L[prr], marr + R[prr]);
}

int query(int sll, int srr, int c)
{
    int pll = belong[sll], prr = belong[srr], res = 0;
    if (pll == prr){
        for (int i = sll; i <= srr; ++ i)
        {
            if (arr[i] + mk[pll] >= c){
                res ++;
            }
        }
        return res;
    }
    for (int i = sll; i <= R[pll]; ++ i)
    {
        if (arr[i] + mk[pll] >= c){
            res ++;
        }
    }
    for (int i = L[prr]; i <= srr; ++ i)
    {
        if (arr[i] + mk[prr] >= c){
            res ++;
        }
    }
    for (int i = pll + 1; i < prr; ++ i)
    {
        auto it = lower_bound(marr + L[i], marr + R[i] + 1, c - mk[i]);
        int t = marr + R[i] + 1 - it;
        res += t >= 0 ? t : 0;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test;
    cin >> n >> test;
    for (int i = 1; i <= n; ++ i)
    {
        cin >> arr[i];
        marr[i] = arr[i];
    }
    tot = sqrt(n);
    for (int i = 1; i <= tot; ++ i)
    {
        L[i] = (i - 1) * tot + 1;
        R[i] = i * tot;
    }
    if (R[tot] < n){
        tot ++ ;
        L[tot] = R[tot - 1] + 1;
        R[tot] = n;
    }
    for (int i = 1; i <= tot; ++ i)
    {
        for (int j = L[i]; j <= R[i]; ++ j)
        {
            belong[j] = i;
        }
        sort(marr + L[i], marr + R[i] + 1);
    }
    while (test --)
    {
        char ch;
        int l, r, c;
        cin >> ch >> l >> r >> c;
        if (ch == 'A'){
            cout << query(l, r, c) << '\n';
        }else{
            add(l, r, c);
        }
    }
    return 0;
}