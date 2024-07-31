#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;
using ll = long long;

i128 power(i128 a, i128 i, i128 p) {
    i128 res = 1 % p;
    while (i) {
        if (i & 1) 
            res = res * a % p;
        a = a * a % p;
        i >>= 1;
    }
    return res;
}

inline i128 C(i128 m, i128 n, i128 p) {
    i128 a = 1, b = 1;
    for (i128 i = n; i > n - m; -- i) {
        a = a * i % p;
    }
    for (i128 i = m; i >= 2; -- i) {
        b = b * i % p;
    }
    return a * power(b, p - 2, p) % p;
}

i128 Lucas(i128 m, i128 n, i128 p) {
    if (n == 0) {
        return 1;
    }
    return C(m % p, n % p, p) * Lucas(m / p, n / p, p) % p;
}

inline void print(i128 n) {
    static int A[300];
    int m = 0;
    
    do {
        A[++ m] = n % 10;
        n /= 10;
    }while(n > 0);

    for (int i = m; i >= 1; -- i) {
        cout << A[i];
    }

    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t --) {
        ll n, m, p;
        cin >> n >> m >> p;

        i128 ans = Lucas(n, n + m, p);

        print(ans);
    }

    return 0;
}