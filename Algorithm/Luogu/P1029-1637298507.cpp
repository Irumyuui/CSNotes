#include <bits/stdc++.h>

#define debug(x) std::cerr << #x << ' : ' << x << std::endl
#define FAST() std::ios::sync_with_stdio(false)

using namespace std;

const int INFI = 0x7FFFFFFF;
typedef long long LL;
typedef long double LD;
typedef pair<int, int> PII;

inline void FREIN(const char *text)
{
    freopen(text, "r", stdin);
}

int x, y;
inline int gcd(int a, int b)
{
    while (b ^= a ^= b ^= a %= b);
    return a;
}

inline bool result(int a, int b)
{
    if (gcd(a, b) == x && a * b / x == y){
        return true;   
    }
    return false;
}

void solve()
{
    cin >> x >> y;
    int ans = 0;
    for (int i = x; i <= y; i += x)
    {
        if (result(i, y * x / i)) ans ++;
    }
    cout << ans;
    return;
}

int main()
{
    FAST();
    solve();
    return 0;
}