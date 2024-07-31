#include <bits/stdc++.h>
using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch=='-') 
            f=-1;
        ch=getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}

inline void write(int x)
{
    static int sta[50];
    int top = 0;
    do{
        sta[top ++] = x % 10, x /= 10;
    }while (x);
    while (top)
        putchar(sta[-- top] + 48);
}

const int LEN = 1e5 + 114;
struct www
{
    int len, i;
    bool operator < (const www &a) const
    {
        return this->len < a.len;
    }
}a[LEN], b[LEN];

int arr[LEN];
long long ans = 0;
const long long MOD = 1e8 - 3;

int t[LEN];
void mergesort(int ll, int rr)
{
    if (rr - ll <= 1){
        return;
    }
    int mid = ll + ((rr - ll) >> 1);
    mergesort(ll, mid);
    mergesort(mid, rr);
    int ap = ll, bp = mid, tp = ll;
    while (ap < mid && bp < rr)
    {
        if (arr[ap] > arr[bp]){
            t[tp ++] = arr[bp ++];
            ans = (ans + mid - ap) % MOD;
        }else{
            t[tp ++] = arr[ap ++];
        }
    }
    while (ap < mid)
    {
        t[tp ++] = arr[ap ++];
    }
    while (bp < rr)
    {
        t[tp ++] = arr[bp ++];
    }
    for (int i = ll; i < rr; ++ i)
    {
        arr[i] = t[i];
    }
}

int main()
{
    int n = read();
    for (int i = 0; i < n; ++ i)
    {
        a[i].len = read();
        a[i].i = i;
    }
    for (int i = 0; i < n; ++ i)
    {
        b[i].len = read();
        b[i].i = i;
    }
    sort(a, a + n);
    sort(b, b + n);
    for (int i = 0; i < n; ++ i)
    {
        arr[a[i].i] = b[i].i;
    }
    mergesort(0, n);
    write(ans);
    return 0;
}