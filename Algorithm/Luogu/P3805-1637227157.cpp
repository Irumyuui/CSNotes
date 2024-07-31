#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

const int LEN = 11000007;
char str[LEN << 1];
int pi[LEN << 1];

inline int read()
{
    int k = 0;
    str[k ++] = '(';
    str[k ++] = '#';
    char x;
    while ((x = getchar()) != EOF)
    {
        str[k ++] = x;
        str[k ++] = '#';
    }
    str[k ++] = ')';
    return k;
}

int manacher(const int &len)
{
    int pos, rlim, ans;
    pos = rlim = ans = 0;
    for (int i = 1; i < len; ++ i)
    {
        if (i < rlim){
            pi[i] = min(pi[(pos << 1) - i], rlim - i);
        }else{
            pi[i] = 1;
        }
        while (str[i - pi[i]] == str[i + pi[i]])
        {
            pi[i] ++;
        }
        if (i + pi[i] > rlim){
            rlim = i + pi[i];
            pos = i;
        }
        ans = max(ans, pi[i]);
    }
    return ans - 1;
}

void solve()
{
    int len = read();
    cout << manacher(len);
    return;
}

int main()
{
    solve();
    return 0;
}