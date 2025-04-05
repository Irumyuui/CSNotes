#include <iostream>

using namespace std;

typedef long long LL;

LL quickPow(LL a, LL i, LL p)
{
    LL res = 1;
    while (i)
    {
        if (i & 1){
            res = res * a % p;
        }
        a = a * a % p;
        i >>= 1;
    }
    return res;
}

int main()
{
    LL a, i, p;
    cin >> a >> i >> p;
    cout << a << "^" << i << " mod " << p << "=" << quickPow(a, i, p);
    return 0;
}