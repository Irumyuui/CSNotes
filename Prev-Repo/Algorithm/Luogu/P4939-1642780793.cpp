#include <bits/stdc++.h>

using namespace std;

const int LEN = 1e7 + 10;
long long d[LEN], n;

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

inline int lowbit(int x)
{
    return x & -x;
}

void add(int x, int k)
{
    while (x <= n)
    {
        d[x] += k;
        x += lowbit(x);
    }
}

long long query(int x)
{
    long long res = 0;
    while (x)
    {
        res += d[x];
        x -= lowbit(x);
    }
    return res;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int t;
    n = read(), t = read();
    while (t --)
    {
        int c;
        c = read();
        if (c == 0){
            int l, r;
            l = read(), r = read();
            add(l, 1);
            add(r + 1, -1);
        }else{
            int x;
            x = read();
            cout << query(x) << '\n';
        }
    }
    return 0;
}