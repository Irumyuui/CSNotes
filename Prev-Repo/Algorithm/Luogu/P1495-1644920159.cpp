#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
using i128 = __int128_t;
using ll = long long;

i128 Exgcd(i128 a, i128 b, i128 &x, i128 &y){
    if (b == 0){
        x = 1; y = 0;
        return a;
    }
    
    i128 d = Exgcd(b, a % b, x, y);

    i128 tmp = x;
    x = y;
    y = tmp - a / b * y;

    return d;
}

i128 CRT(i128 cnt, i128 *a, i128 *m){
    i128 M = 1, ans = 0;

    for (int i = 0; i < cnt; ++ i){
        M *= m[i];
    }

    for (int i = 0; i < cnt; ++ i){
        i128 Mk = M / m[i], y, x;
        Exgcd(Mk, m[i], y, x);
        y = (y % m[i] + m[i]) % m[i];
        ans = (ans + a[i] * Mk * y) % M;
    }

    return ans;
}

i128 a[100], m[100];

template<typename T> inline void print(T x){
    static int A[100];

    int m = 0;

    do{
        A[++ m] = x % 10;
        x /= 10;
    }while (x > 0);

    for (int i = m; i >= 1; -- i){
        cout << A[i];
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    int n;
    cin >> n;

    for (int i = 0; i < n; ++ i){
        ll x, y;
        cin >> x >> y;
        m[i] = x;
        a[i] = y;
    }

    i128 ans = CRT(n, a, m);

    print(ans);

    return 0;
}