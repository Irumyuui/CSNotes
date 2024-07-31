#include <bits/stdc++.h>
using namespace std;
#define all(x) begin(x), end(x)
typedef long long LL;
#define range(x, a, b) for (LL x = a; x <= b; ++ x)
#define arange(x, b, a) for (LL x = b; x >= a; -- x)
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;

LL Exgcd(LL a, LL b, LL &x, LL &y)
{
    if (b == 0){
        x = 1, y = 0;
        return a;
    }
    LL d = Exgcd(b, a % b, x, y);
    LL t = x;
    x = y;
    y = t - a / b * y;
    return d;
}

int main()
{
    std::ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    LL a , b, x, y;
    cin >> a >> b;
    LL d = Exgcd(a, b, x, y);
    cout << (x % b + b) % b;
    return 0;
}